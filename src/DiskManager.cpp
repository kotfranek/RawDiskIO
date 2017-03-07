/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DiskIO.cpp
 * Author: p.podwapinski
 * 
 * Created on March 3, 2017, 2:26 PM
 */

#include <string>
#include <iostream>

#include "Windows.h"

#include "types.h"
#include "log.h"
#include "DiskManager.h"
#include "DiskGeometry.h"
#include "DeviceFile.h"
#include "PartitionIO.h"

namespace
{
    const size_t MAX_DRIVES_COUNT = 'Z'-'A';
    
    const wchar_t P_DRIVE_PATH[] = L"\\\\.\\PhysicalDrive";
    
    /**
     * Convert the WINAPI Geometry to internally used class
     * @param geometry
     * @return 
     */
    ::rawio::DiskGeometry makeGeometry( const DISK_GEOMETRY& geometry )
    {
        const uint64_t sectorCount = geometry.Cylinders.QuadPart * \
            uint64_t( geometry.TracksPerCylinder ) * \
            uint64_t( geometry.SectorsPerTrack ); 
        return ::rawio::DiskGeometry( sectorCount, geometry.BytesPerSector );
    }    
}

namespace rawio
{
    DiskManager::DiskManager() 
        : m_disks()
    {
    }
    
    bool DiskManager::init()
    {
        bool result = false;
        
        const DWORD logicalDrives = GetLogicalDrives();                
        
        if ( 0U != logicalDrives )
        {
            wchar_t driveLetter = L'A';
            for ( size_t i = 0U; i < MAX_DRIVES_COUNT; i++ )
            {
                if ( IS_BIT( logicalDrives, i ) )
                {
                    readDrive( driveLetter + i );    
                }                    
            }
            LOG_I( L"Disk(s): " << m_disks.size() << L", Partition(s): " << m_partitions.size() );
            result = true;
        }
        
        return result;
    }
    
    void DiskManager::readDrive( const wchar_t letter )
    {                
        ::std::wstring userPath;
        userPath.push_back( letter );
        userPath.append( L":\\" );
        
        PartitionIO partIo( letter );
        const TPhysicalDiskId diskNum = partIo.getDiskId();
        
        if ( diskNum != INVALID_DISKID )
        {
            LOG_I( L"Adding Disk No.: " << diskNum << L" / Part.: " 
                    << letter << L" / Type: " 
                    << GetDriveTypeW( userPath.c_str() )
                    << L" / Size: " << partIo.getLength() / ( 1024 * 1024 ) );

            m_disks.insert( diskNum );
            m_partitions.push_back( PartitionInfo( letter, diskNum ) );
        }
        else
        {
            LOG_E( L"Volume '" << userPath << L"' is not supported" );
        }                        
    }
        
    PhysicalDiskInfo DiskManager::getDevice( const PartitionInfo& partition ) const
    {        
        const TPhysicalDiskId id = partition.getDiskId();
        DiskGeometry geom;
        
        ::std::wstring path( P_DRIVE_PATH );
        path.append( ::std::to_wstring( id ) );

        DeviceFile phyDisk;    

        if ( phyDisk.open( path ) )
        {
            DISK_GEOMETRY win32Geom = { 0 };

            if ( phyDisk.ioCtl( IOCTL_DISK_GET_DRIVE_GEOMETRY, win32Geom ) )
            {                  
                geom = ::makeGeometry( win32Geom );
            }
        }    
        
        return PhysicalDiskInfo( id, geom );
    }
    
    
    DiskManager::~DiskManager() 
    {
    }

};

