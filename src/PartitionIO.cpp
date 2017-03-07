/*
 * Copyright (c) 2017, p.podwapinski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* 
 * File:   PartitionIO.cpp
 * Author: p.podwapinski
 * 
 * Created on March 7, 2017, 11:06 AM
 */

#include <windows.h>
#include <iostream>
#include "log.h"
#include "DeviceFile.h"
#include "PartitionIO.h"
#include "PartitionInfo.h"

namespace
{
    const wchar_t VOLUME_PATH[] = L"\\\\.\\";

    ::std::wstring mkSysPath( const wchar_t letter )
    {
        ::std::wstring sysPath( ::VOLUME_PATH );
        sysPath.push_back( letter );
        sysPath.push_back( L':' );          
        
        return ::std::move( sysPath );
    }
}

namespace rawio
{
PartitionIO::PartitionIO(const wchar_t letter) 
    : m_letter( letter )
{
}

PartitionIO::PartitionIO( const PartitionInfo& info )
    : PartitionIO( info.getLetter() )
{    
}


uint64_t PartitionIO::getLength() const
{
    uint64_t result = 0U;
    
    PARTITION_INFORMATION_EX pInfo;
    
    if ( DeviceFile().ioCtl( ::mkSysPath( m_letter ), IOCTL_DISK_GET_PARTITION_INFO_EX , pInfo ) )
    {                        
        result = pInfo.PartitionLength.QuadPart;
    }     
    {
        LOG_E( L"Unable to query '" << m_letter << L":' volume" );
    }    
    
    return result;
}


TPhysicalDiskId PartitionIO::getDiskId() const
{
    TPhysicalDiskId result = INVALID_DISKID;    
    VOLUME_DISK_EXTENTS extents = { 0 };
    
    if ( DeviceFile().ioCtl( ::mkSysPath( m_letter ), IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS, extents ) )
    {                        
        if ( 1U == extents.NumberOfDiskExtents )
        {
            result = extents.Extents[0].DiskNumber;
        }
        else
        {
            LOG_E( L"Partition '" << m_letter << L":' split between more disks, not supported" );
        }
    }                               
    
    return result;
}


bool PartitionIO::dump( const ::std::wstring& file )
{
    bool result = false;
    
    DeviceFile volume;
    
    if ( volume.open( ::mkSysPath( m_letter ), false ) )        
    {
        volume.flush();
        volume.close();
        
        volume.open( ::mkSysPath( m_letter ) );
        if ( volume.ioCtl( FSCTL_LOCK_VOLUME ) && volume.ioCtl( FSCTL_DISMOUNT_VOLUME ) )
        {
            File output;
            
            if( output.open( file, GENERIC_WRITE, 0, CREATE_ALWAYS ) )
            {
                uint8_t buffer[ 1024 ] = {0};
                
                volume.read( buffer, 1024 );
                output.write( buffer, 1024 );
                
                result = true;    
            }            
        }
        else
        {
            LOG_E( L"Partition '" << m_letter << L":' not locked" );
        }                
    }            
    return result;    
}

PartitionIO::~PartitionIO() 
{
}    
};

