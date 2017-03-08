/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DeviceFile.h
 * Author: p.podwapinski
 *
 * Created on March 6, 2017, 10:26 AM
 */

#ifndef DEVICEFILE_H
#define DEVICEFILE_H

#include <string>
#include "File.h"

namespace rawio
{
    class DeviceFile : public File
    {
    public:
        DeviceFile();
                
        /**
         * Open a device file. 
         * @param path File location
         * @return true if successful
         */        
        bool open(const ::std::wstring& path, const bool writable = false);
        
        
        bool ioCtl( const DWORD ctlCode, void* output = NULL, size_t size = 0U );
        
        /**
         * Perform a no-input Device IO Control operation
         * @param ctlCode Operation Code
         * @param output Output Buffer
         * @return true on success
         */
        template<typename T>bool ioCtl( const DWORD ctlCode, T& output )
        {
            return ioCtl( ctlCode, &output, sizeof( output ) );            
        }
        
        /**
         * Perform a single Opena and no-input Device IO Control operation
         * @param path Device to open
         * @param ctlCode Operation Code
         * @param output Output Buffer
         * @return true on success
         */
        template<typename T>bool ioCtl( const ::std::wstring& path, const DWORD ctlCode, T& output )
        {
            return open( path ) && ioCtl( ctlCode, output );
        }
        
        
        bool ioCtl( const ::std::wstring& path, const DWORD ctlCode )
        {
            return open( path ) && ioCtl( ctlCode );
        }
        
    private:
        DeviceFile(const DeviceFile& orig);
    };
};
#endif /* DEVICEFILE_H */

