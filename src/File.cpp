/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File.cpp
 * Author: Przemysław
 * 
 * Created on 6 marca 2017, 19:51
 */

#include "log.h"
#include "File.h"

namespace rawio
{

File::File() 
    : m_file( INVALID_HANDLE_VALUE )
{
}


bool File::open(const ::std::wstring& path, const DWORD access , const DWORD share )
{
    bool result = false;
    
    if ( m_file == INVALID_HANDLE_VALUE && !path.empty() )
    {
        m_file = ::CreateFileW( path.c_str(), access
                , share
                , NULL
                , OPEN_EXISTING
                , 0
                , NULL );
        
        if ( m_file != INVALID_HANDLE_VALUE )
        {
            result = true;
        }
        else
        {
            LOG_E( L"Error opening [" << path << L"]: " << ::GetLastError() );
        }
    }
    
    return result;
}


void File::flush()
{
    if ( m_file == INVALID_HANDLE_VALUE )
    {    
        if ( 0 == ::FlushFileBuffers( m_file ) )
        {
            LOG_E( L"::FlushFileBuffers() returned '" << ::GetLastError() << L"'" );
        }
    }
}

void File::close()
{
    if ( m_file != INVALID_HANDLE_VALUE )
    {
        ::CloseHandle( m_file );
        m_file = INVALID_HANDLE_VALUE;
    }
}



};
