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
    
    const size_t SEGMENT = 32 * 1024U;
    
    /* Number of blocks to be copied in one hit */
    const size_t COPY_BLOCKS = 64U;
    
    bool CopyFiles( ::rawio::File& dst, const ::rawio::File& src, const size_t blockSize )
    {
        const size_t length = blockSize * ::COPY_BLOCKS;
        uint8_t* buffer = (uint8_t*) ::malloc( length );

        while ( 0U != src.read( buffer, length ) )
        {
            dst.write( buffer, length );    
        }
        
        ::free( buffer );
        
        return true;
    }
    
    ::std::wstring MkSysPath( const wchar_t letter )
    {
        ::std::wstring sysPath( ::VOLUME_PATH );
        sysPath.push_back( letter );
        sysPath.push_back( L':' );          
        
        return ::std::move( sysPath );
    }
    
    bool LockAndDismount( ::rawio::DeviceFile& volume )
    {
        return volume.ioCtl( FSCTL_LOCK_VOLUME ) && volume.ioCtl( FSCTL_DISMOUNT_VOLUME );
    }
}

namespace rawio
{
PartitionIO::PartitionIO(const wchar_t letter) 
    : m_letter( letter )
{
}

PartitionIO::PartitionIO( const PartitionInfo& info )
    : PartitionIO( info.getType() )
{    
    }

VolumeLocation PartitionIO::getVolumeLocation() const 
{
    TPhysicalDiskId id = INVALID_DISKID;
    uint64_t offset = 0U;
    uint64_t length = 0U;
    
    VOLUME_DISK_EXTENTS extents = { 0 };
    
    if ( DeviceFile().ioCtl( ::MkSysPath( m_letter ), IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS, extents ) )
    {                        
        if ( 1U == extents.NumberOfDiskExtents )
        {
            id = extents.Extents[0].DiskNumber;
            offset = extents.Extents[0].StartingOffset.QuadPart;
            length = extents.Extents[0].ExtentLength.QuadPart;
        }
        else
        {
            LOG_E( L"Partition '" << m_letter << L":' split between more disks, not supported" );
        }
    }        
    
    return VolumeLocation( id, offset, length );
}



uint64_t PartitionIO::getLength() const
{
    uint64_t result = 0U;
    
    GET_LENGTH_INFORMATION pInfo;
    
    if ( DeviceFile().ioCtl( ::MkSysPath( m_letter ), IOCTL_DISK_GET_LENGTH_INFO , pInfo ) )
    {                        
        result = pInfo.Length.QuadPart;
    }    
    else
    {
        LOG_E( L"Unable to query '" << m_letter << L":' volume" );
    }    
    
    return result;
}


TPhysicalDiskId PartitionIO::getDiskId() const
{
    TPhysicalDiskId result = INVALID_DISKID;    
    VOLUME_DISK_EXTENTS extents = { 0 };
    
    if ( DeviceFile().ioCtl( ::MkSysPath( m_letter ), IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS, extents ) )
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

bool PartitionIO::dump(const ::std::wstring& file, const size_t blockSize ) const
{
    bool result = false;
    
    DeviceFile volume;
    
    if ( volume.open( ::MkSysPath( m_letter ), true ) )        
    {
        volume.flush();
        volume.close();
        
        volume.open( ::MkSysPath( m_letter ) );
        if ( ::LockAndDismount( volume ) )
        {
            File output;
            
            if( output.open( file, File::WRITE_NEW ) )
            {                            
                result = ::CopyFiles( output, volume, blockSize );    
            }            
        }
        else
        {
            LOG_E( L"Partition '" << m_letter << L":' not locked" );
        }                
    }            
    return result;
}

bool PartitionIO::load( const ::std::wstring& file )
{
    bool result = false;
    
    DeviceFile volume;
            
    if ( volume.open( ::MkSysPath( m_letter ), true ) )
    {
        if ( ::LockAndDismount( volume ) )
        {
            File input;

            if( input.open( file, File::READ_EXISTING ) )
            {        
                result = ::CopyFiles( volume, input, 512U );
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

