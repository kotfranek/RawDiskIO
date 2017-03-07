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

namespace rawio
{

PartitionInfo::PartitionInfo( const wchar_t letter, const TPhysicalDiskId diskId ) 
    : m_letter( letter )
    , m_phyDevId( diskId )
{
}

PartitionInfo::~PartitionInfo() 
{
}

};
