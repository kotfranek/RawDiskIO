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
            ::std::wcout << L"D[" << info.getId() << L"]: P-> T:" << (*i).getStyle() << L"S: " << (*i).getSize() / 1024U << L" kB" << ::std::endl;                        
                        
            ++i;
        }
    }
                    
    return 0;
}
