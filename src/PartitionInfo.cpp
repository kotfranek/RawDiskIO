/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Partition.cpp
 * Author: p.podwapinski
 * 
 * Created on March 3, 2017, 2:25 PM
 */

#include "PartitionInfo.h"
#include "VolumeLocation.h"

namespace rawio
{

PartitionInfo::PartitionInfo( const uint8_t type, const VolumeLocation& location ) 
    : m_type( type )
    , m_vLoc( location )
{
}

PartitionInfo::~PartitionInfo() 
{
}

};
