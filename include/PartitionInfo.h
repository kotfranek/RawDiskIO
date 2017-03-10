/* 
 * File:   Partition.h
 * Author: p.podwapinski
 *
 * Created on March 3, 2017, 2:25 PM
 */

#ifndef PARTITION_H
#define PARTITION_H

#include <cstdint>
#include <vector>

#include "types.h"
#include "VolumeLocation.h"

namespace rawio
{
    class PartitionInfo {
    public:
        explicit PartitionInfo( const uint8_t type, const VolumeLocation& location );
        
        /**
         * Get partition letter
         */
        uint8_t getType() const
        {
            return m_type;
        }
        
        /**
         * Check if partition is mounted with the given letter
         * @param letter
         * @return true, if the mount point matches
         */
        bool isLetter( const wchar_t letter ) const
        {
            return letter == getType();
        }
        
        /**
         * Get the partition size in bytes
         * @return 
         */
        uint64_t getSize() const
        {
            return m_vLoc.m_length;
        }
        
        /**
         * Get Physical Device id
         * @return 
         */
        TPhysicalDiskId getDiskId() const
        {
            return m_vLoc.m_diskId;
        }
        
        
        virtual ~PartitionInfo();
    private:        
        /* Partition type */
        uint8_t m_type;
        
        /* Volume location */
        VolumeLocation m_vLoc;
    };
    
    typedef ::std::vector<PartitionInfo> TPartitionArray;    
};
#endif /* PARTITION_H */

