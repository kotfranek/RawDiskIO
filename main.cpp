#include <windows.h>
#include <stdio.h>
#include <iostream>

#include "DiskManager.h"
#include "PhysicalDiskIO.h"
#include "PartitionIO.h"

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
            ::rawio::PhysicalDiskInfo info = diskIo.getDevice( (*i) );            
            ::std::wcout << L"P->" << (*i).getLetter() << L":" << ::std::endl;            
            ::std::wcout << L"D->" << info.getId() << L", size = " << info.geometry().sizeB() / ( 1024U * 1024U ) << L" MB" << ::std::endl;            
            
            if ( (*i).getLetter() == 'E' )
            {
                ::rawio::PartitionIO( (*i) ).dump( L"C:\\duupaaaa.txt" );
                //diskIo.umount( (*i) );
            }
            
            if ( info.geometry().sizeB() < 4000000000 )
            {
                pendriveE = info;
                ::std::wcout << L"Will use disk '" << info.getId() << L"'" << ::std::endl;
            }
            
            ++i;
        }
        
        //::rawio::PhysicalDiskIO phyDisk( pendriveE );
    }
    
    return 0;
}
