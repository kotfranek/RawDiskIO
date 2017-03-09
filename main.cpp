#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "api/DiskManager.h"

int main(void)
{
    ::rawio::DiskManager diskIo;    
    
    if( diskIo.init() )
    {        
        ::rawio::PhysicalDiskInfo pendriveE;
        
        const auto partitions = diskIo.partitions();
        auto i = partitions.begin();                
        
        while ( i != partitions.end() )
        {
            ::rawio::PhysicalDiskInfo info = diskIo.getDiskInfo( (*i) );            
            ::std::wcout << L"P->" << (*i).getLetter() << L":" << ::std::endl;            
            ::std::wcout << L"D->" << info.getId() << L", size = " << info.geometry().sizeB() / ( 1024U * 1024U ) << L" MB" << ::std::endl;            
            
            if ( (*i).getLetter() == 'D' )
            {
                diskIo.load( (*i), L"C:\\Projects\\temp\\2017-03-02-raspbian-jessie-lite.img" );
            }            
            
            ++i;
        }
        
        wchar_t volume[ 1024 ];
        const HANDLE hnd = FindFirstVolumeW( volume, sizeof( volume ) );
        
        do
        {
            wchar_t DeviceName[ 1024 ];
            auto Index = wcslen(volume) - 1;
            //  QueryDosDeviceW does not allow a trailing backslash,
            //  so temporarily remove it.
            volume[Index] = L'\0';

            auto CharCount = QueryDosDeviceW(&volume[4], DeviceName, ARRAYSIZE(DeviceName));            
            ::std::wcout << L"Volume '" << volume << L"'" << ::std::endl;
            ::std::wcout << L"Device '" << DeviceName << L"'" << ::std::endl;
            
            volume[Index] = L'\\';            
        } 
        while ( 0 != FindNextVolumeW( hnd, volume, sizeof( volume ) ) );
        
        FindVolumeClose( hnd );
        
        //::rawio::PhysicalDiskIO phyDisk( pendriveE );
    }
    
    return 0;
}
