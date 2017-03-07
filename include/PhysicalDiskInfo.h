/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PhysicalDisk.h
 * Author: p.podwapinski
 *
 * Created on March 3, 2017, 3:50 PM
 */

#ifndef PHYSICALDISK_H
#define PHYSICALDISK_H

#include <vector>
#include "DiskGeometry.h"

namespace rawio
{    
    class PartitionInfo;
    
    class PhysicalDiskInfo 
    {
    public:
        PhysicalDiskInfo( const uint32_t id, const DiskGeometry& geom );        
        PhysicalDiskInfo();        
               
        /**
         * Disk Id
         * @return 
         */
        uint32_t getId() const
        {
            return m_id;
        }
        
        /**
         * Expose the geometry
         * @return 
         */
        const DiskGeometry& geometry() const
        {
            return m_geometry;
        }
        
    private:        
        uint32_t m_id;
        uint32_t m_attributes;
        DiskGeometry m_geometry;        
    };
    
    typedef ::std::vector<PhysicalDiskInfo> TPhysicalDisks;
};

#endif /* PHYSICALDISK_H */

