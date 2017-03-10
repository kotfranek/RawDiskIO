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
#include <Winioctl.h>

#include "api/DiskManager.h"
#include "api/IProgressListener.h"

#include "types.h"
#include "log.h"
#include "DiskGeometry.h"
#include "DeviceFile.h"
#include "PartitionIO.h"

namespace
{
    /* Handle maximum 64 disks */
    const size_t MAX_PHY_DISK_COUNT = 64U;
    
    /* Handle maximum 32 partitions per disk */
    const size_t MAX_PARTITION_COUNT = 32U;
    
    
    const size_t MAX_DRIVES_COUNT = 'Z'-'A';
    
    /* Generic Physical Drive path */
    const wchar_t PHY_DRIVE_PATH[] = L"\\\\.\\PhysicalDrive";
    
    /* Generic Harddisk path */
    const wchar_t HARDDISK_PATH[] = L"\\\\?\\GLOBALROOT\\Device\\Harddisk";
    
    /* Generic Partition Sub-Path */
    const wchar_t PARTITION_SUBPATH[] = L"\\Partition";
    
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
    
    /**
     * Make Physical Drive path
     * @param id
     * @return Path
     */
    ::std::wstring MkPhyDrvPath( const size_t id )
    {
        ::std::wstring path( PHY_DRIVE_PATH );
        path.append( ::std::to_wstring( id ) );
        
        return ::std::move( path );
    }
    
    /**
     * Make Partition path
     * @param id
     * @param n
     * @return Path
     */
    ::std::wstring MkPartitionPath( const size_t id, const size_t n )
    {
        ::std::wstring path( HARDDISK_PATH );
        path.append( ::std::to_wstring( id ) );
        path.append( PARTITION_SUBPATH );
        path.append( ::std::to_wstring( n ) );
        
        return ::std::move( path );
    }    
}

namespace rawio
{
    DiskManager::DiskManager() 
        : m_disks()
    {
    }
    
    void DiskManager::init()
    {       
        DeviceFile phyDisk;
        DeviceFile partition;
        
        for ( size_t i = 0U; i < MAX_PHY_DISK_COUNT; i++ )
        {
            if ( phyDisk.open( ::MkPhyDrvPath( i ) ) )
            {
                m_disks.insert( i );
                phyDisk.close();
                
                for( size_t j = 0U; j < MAX_PARTITION_COUNT; j++ )
                {                    
                    if ( partition.open( ::MkPartitionPath( i, j ) ) )
                    {
                        VOLUME_DISK_EXTENTS extents;
                        PARTITION_INFORMATION_EX information;                        
                        
                        partition.ioCtl( IOCTL_VOLUME_GET_VOLUME_DISK_EXTENTS, extents );
                        partition.ioCtl( IOCTL_DISK_GET_PARTITION_INFO_EX , information );
                        
                        partition.close();

                        const uint64_t offset = extents.Extents[0].StartingOffset.QuadPart;
                        const uint64_t length = extents.Extents[0].ExtentLength.QuadPart;
                        
                        m_partitions.push_back( PartitionInfo( information.PartitionStyle, VolumeLocation( i, offset, length ) ) );
                    }
                }               
            }
        }
        
        LOG_I( L"Disk(s): " << m_disks.size() << L", Partition(s): " << m_partitions.size() );                        
    }       
        
    PhysicalDiskInfo DiskManager::getDiskInfo( const PartitionInfo& partition ) const
    {        
        const TPhysicalDiskId id = partition.getDiskId();
        DiskGeometry geom;
        
        ::std::wstring path( PHY_DRIVE_PATH );
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
    
    
    bool DiskManager::dump( const PartitionInfo& partition, const ::std::wstring& file
        , const IProgressListener* listener ) const
    {
        return PartitionIO( partition ).dump( file );
    }
    
    bool DiskManager::load(const TPhysicalDiskId id, const ::std::wstring& file
        , const IProgressListener* listener) const 
    {
        return false;
    }
    

    bool DiskManager::load(const PartitionInfo& partition, const ::std::wstring& file
        , const IProgressListener* listener) const 
    {
        return PartitionIO( partition ).load( file );
    }
        
    DiskManager::~DiskManager() 
    {
    }

};

