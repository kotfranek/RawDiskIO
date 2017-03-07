/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DiskGeometry.h
 * Author: p.podwapinski
 *
 * Created on March 3, 2017, 4:28 PM
 */

#ifndef DISKGEOMETRY_H
#define DISKGEOMETRY_H

#include <cstdint>

namespace rawio
{
    class DiskGeometry 
    {
    public:
        DiskGeometry();
        DiskGeometry( const uint64_t sectorCount, const uint32_t sectorSize );
        
        /**
         * Calculate the size in bytes
         */
        uint64_t sizeB() const
        {
            return m_sectorCount * uint64_t( m_sectorSize );
        }
        
        uint64_t m_sectorCount;
        uint32_t m_sectorSize;
    private:
        //DiskGeometry(const DiskGeometry& orig);
        //DiskGeometry& operator=( const DiskGeometry& );
    };
};
#endif /* DISKGEOMETRY_H */

