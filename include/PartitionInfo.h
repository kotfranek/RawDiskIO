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

namespace rawio
{
    class PartitionInfo {
    public:
        explicit PartitionInfo( const wchar_t letter, const TPhysicalDiskId diskId, const uint64_t size );
        
        /**
         * Get partition letter
         */
        wchar_t getLetter() const
        {
            return m_letter;
        }
        
        /**
         * Check if partition is mounted with the given letter
         * @param letter
         * @return true, if the mount point matches
         */
        bool isLetter( const wchar_t letter ) const
        {
            return letter == getLetter();
        }
        
        /**
         * Get the partition size in bytes
         * @return 
         */
        uint64_t getSize() const
        {
            return m_size;
        }
        
        /**
         * Get Physical Device id
         * @return 
         */
        TPhysicalDiskId getDiskId() const
        {
            return m_phyDevId;
        }
        
        
        virtual ~PartitionInfo();
    private:        
        /* Logical Partition letter */
        wchar_t m_letter;
        
        /* Partition size in bytes */
        uint64_t m_size;
        
        /* Physical Device Id */
        TPhysicalDiskId m_phyDevId;
    };
    
    typedef ::std::vector<PartitionInfo> TPartitionArray;    
};
#endif /* PARTITION_H */

