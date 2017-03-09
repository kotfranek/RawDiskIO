/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File.h
 * Author: Przemysław
 *
 * Created on 6 marca 2017, 19:51
 */

#ifndef FILE_H
#define FILE_H

#include <cstdint>
#include <string>
#include <Windows.h>

namespace rawio
{
    class File 
    {
    public:
        
        struct OpenParameters
        {
            DWORD m_access;
            DWORD m_share;
            DWORD m_creation;
        };
        
        static const OpenParameters READ_EXISTING;
        static const OpenParameters WRITE_EXISTING;
        static const OpenParameters WRITE_NEW;
        
        File();    
        
        /**
         * Open a file, which exists
         * @param path File location
         * @return true if successful
         */
        bool open( const ::std::wstring& path, const OpenParameters& params );
        
        /**
         * Flush the buffers
         */
        void flush();
        
        /**
         * Close the File
         */
        void close();
        
        
        /**
         * Write N bytes into the file
         * @param src Source buffer
         * @param bytes
         */
        size_t write( const void* src, const size_t bytes );
        
        /**
         * Read from file to the given buffer
         * @param src
         * @param bytes
         */
        size_t read( void* dst, const size_t bytes ) const;
                        
        virtual ~File()
        {
            close();
        }
        
    protected:
        HANDLE getNativeHandle() const
        {
            return m_file;
        }
        
    private:
        File(const File& orig);
              
        /* File handle */
        HANDLE m_file;        
    };    
};

#endif /* FILE_H */

