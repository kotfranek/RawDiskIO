#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "api/DiskManager.h"

int main(void)
{
    ::rawio::DiskManager diskIo;    
    diskIo.init();

    {        
        ::rawio::PhysicalDiskInfo pendriveE;
        
        const auto partitions = diskIo.partitions();
        auto i = partitions.begin();                
        
        while ( i != partitions.end() )
        {
            ::rawio::PhysicalDiskInfo info = diskIo.getDiskInfo( (*i) );            
            ::std::wcout << L"D[" << info.getId() << L"]: P-> T:" << (*i).getType() << L"S: " << (*i).getSize() / 1024U << L" kB" << ::std::endl;                        
            
            if ( (*i).getType() == 'N' )
            {
                diskIo.load( (*i), L"C:\\Projects\\temp\\2017-03-02-raspbian-jessie-lite.img" );
            }            
            
            ++i;
        }
    }
                    
    return 0;
}
