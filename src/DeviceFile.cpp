/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DeviceFile.cpp
 * Author: p.podwapinski
 * 
 * Created on March 6, 2017, 10:26 AM
 */

#include "log.h"
#include "DeviceFile.h"

namespace rawio 
{

DeviceFile::DeviceFile() 
    : File()
{
}


bool DeviceFile::open(const ::std::wstring& path, const bool readOnly )
{
    const DWORD access = readOnly ? GENERIC_READ : GENERIC_READ | GENERIC_WRITE;
    return File::open( path, access, FILE_SHARE_READ | FILE_SHARE_WRITE );
}

bool DeviceFile::ioCtl( const DWORD ctlCode, void* output, size_t size ) 
{
    bool result = false;

    if ( getNativeHandle() != INVALID_HANDLE_VALUE )
    {
        DWORD readB = 0U;
        if ( 0 != ::DeviceIoControl( getNativeHandle()
                            , ctlCode
                            , NULL
                            , 0
                            , output
                            , size
                            , &readB,
                            NULL
                            ) )
        {
            result = true;
        }
        else
        {
            LOG_E( L"IoControl failed: " << ::GetLastError() << L"(" << ctlCode << L"," << output << L"," << size << L")" );
        }
    }    

    return result;     
}

    
};

