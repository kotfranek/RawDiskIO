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
            
            if ( (*i).getLetter() == 'N' )
            {
                diskIo.load( (*i), L"C:\\Projects\\temp\\2017-03-02-raspbian-jessie-lite.img" );
            }            
            
            ++i;
        }
    }
    
    return 0;
}
