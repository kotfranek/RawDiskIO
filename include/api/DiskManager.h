/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DiskIO.h
 * Author: p.podwapinski
 *
 * Created on March 3, 2017, 2:26 PM
 */

#ifndef DISKIO_H
#define DISKIO_H

#include <unordered_set>
#include "PhysicalDiskInfo.h"
#include "PartitionInfo.h"

namespace rawio
{
    class IProgressListener;
    
    class DiskManager 
    {
        typedef ::std::unordered_set<TPhysicalDiskId> TDisksSet;
    public:
        DiskManager();        
        
        /**
         * Initialize the engine
         */
        bool init();
        
        /**
         * Expose partition information.
         * This can be called only after the init method.
         * @return available partitions
         */
        const TPartitionArray& partitions() const
        {
            return m_partitions;
        }
        
        /**
         * Create the PhysicalDisk information for the given partition
         * @param partition
         * @return 
         */
        PhysicalDiskInfo getDiskInfo( const PartitionInfo& partition ) const;
        
        /**
         * Dump partition into file
         * @param partition
         * @param file
         * @return 
         */
        bool dump( const PartitionInfo& partition, const ::std::wstring& file
            , const IProgressListener* listener = NULL ) const;
        
        /**
         * Load raw partition data from file
         * @param partition
         * @param file
         * @param listener
         * @return 
         */
        bool load( const PartitionInfo& partition, const ::std::wstring& file
            , const IProgressListener* listener = NULL ) const;
        
        /**
         * Load raw disk image from file
         * @param disk id
         * @param file
         * @param listener
         * @return 
         */
        bool load( const TPhysicalDiskId id, const ::std::wstring& file
            , const IProgressListener* listener = NULL ) const;        
                
        virtual ~DiskManager();
                
    private:
        /**
         * Get Device info for the given Logical Drive
         * @param letter
         */
        void readDrive( const wchar_t letter );
        /* Actual disk devices */
        TDisksSet m_disks;
        
        /* Partitions */
        TPartitionArray m_partitions;
    };    
};

#endif /* DISKIO_H */

