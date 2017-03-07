/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DiskGeometry.cpp
 * Author: p.podwapinski
 * 
 * Created on March 3, 2017, 4:28 PM
 */

#include "DiskGeometry.h"

namespace rawio
{

DiskGeometry::DiskGeometry() 
    : DiskGeometry( 0U, 0U )
{
}


DiskGeometry::DiskGeometry( const uint64_t sectorCount, const uint32_t sectorSize )
    : m_sectorCount( sectorCount )
    , m_sectorSize( sectorSize )
{    
}
    
};

