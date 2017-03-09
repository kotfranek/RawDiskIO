# CMake minimum version dependency
cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR )

# Project name
project( "RawDiskIO" )

# Compiler and linker flags
set( CPP_COMPILE_FLAGS "-g -Wall -std=c++11" )
set( CPP_LINK_FLAGS "-pthread" )

set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -o3 -s")

# Header files locations
include_directories(
    include
)


add_library( rawdiskio SHARED
    src/DiskGeometry.cpp
    src/DiskManager.cpp
    src/PartitionInfo.cpp
    src/PartitionIO.cpp
    src/PhysicalDiskInfo.cpp
    src/PhysicalDiskIO.cpp
    src/DeviceFile.cpp
    src/File.cpp
)

# Demo application: sources
add_executable( rawdiskio-d
    main.cpp
)

# Demo application: compiler definitions
target_compile_definitions( rawdiskio
    PUBLIC LOG_ENABLED
)

target_compile_definitions( rawdiskio-d
    PUBLIC LOG_ENABLED
)

# Demo application: required libraries
target_link_libraries( rawdiskio-d
    rawdiskio
)

# Set the compiler and linker flags for particular targets
set_target_properties( rawdiskio PROPERTIES COMPILE_FLAGS ${CPP_COMPILE_FLAGS} )
set_target_properties( rawdiskio-d PROPERTIES COMPILE_FLAGS ${CPP_COMPILE_FLAGS} )
set_target_properties( rawdiskio-d PROPERTIES LINK_FLAGS ${CPP_LINK_FLAGS} )