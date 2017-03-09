/*
 * Copyright (c) 2017, p.podwapinski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* 
 * File:   VolumeLocation.h
 * Author: p.podwapinski
 *
 * Created on March 9, 2017, 2:30 PM
 */

#ifndef VOLUMELOCATION_H
#define VOLUMELOCATION_H

#include "types.h"

namespace rawio
{
    class VolumeLocation
    {
    public:
        explicit VolumeLocation( const TPhysicalDiskId id, const uint64_t offset, const uint64_t length )
            : m_diskId( id )
            , m_offset( offset )
            , m_length( length )
        {            
        }
            
        uint32_t lengthKB() const
        {
            return m_length / 1024U;
        }
        
        uint32_t lengthMB() const
        {
            return lengthKB() / 1024U;
        }
        
        /* Physical Disk Id */
        const TPhysicalDiskId m_diskId;
        /* Volume offset */
        const uint64_t m_offset;
        /* Volume Length */
        const uint64_t m_length;
    };
}

#endif /* VOLUMELOCATION_H */

