/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   types.h
 * Author: p.podwapinski
 *
 * Created on March 3, 2017, 2:29 PM
 */

#ifndef TYPES_H
#define TYPES_H

#include <cstdint>


#define BIT( X ) ( 1 << X )

#define IS_BIT( VAL, X ) (VAL) & BIT( (X) )

namespace rawio
{
    typedef uint32_t TPhysicalDiskId;
    
    static const TPhysicalDiskId INVALID_DISKID = 0xFFFF;
};

#endif /* TYPES_H */

