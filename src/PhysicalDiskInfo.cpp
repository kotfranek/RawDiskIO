/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PhysicalDisk.cpp
 * Author: p.podwapinski
 * 
 * Created on March 3, 2017, 3:50 PM
 */

#include <string>
#include <iostream>

#include "log.h"
#include "PhysicalDiskInfo.h"

namespace rawio
{
    
PhysicalDiskInfo::PhysicalDiskInfo( const uint32_t id, const DiskGeometry& geom ) 
    : m_id( id )
    , m_attributes( 0U )
    , m_geometry( geom )
{
}

PhysicalDiskInfo::PhysicalDiskInfo()
    : PhysicalDiskInfo( 0xFFFFFFFF, DiskGeometry() )
{    
}

};

