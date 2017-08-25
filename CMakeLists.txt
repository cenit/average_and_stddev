cmake_minimum_required (VERSION 3.1)
project (average_and_stddev)
set (CMAKE_CXX_STANDARD 11)

set (MAJOR_VERSION 1)
set (MINOR_VERSION 2)

### Set output directories on a per-configuration base
# Single configuration
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )
# Multi configuration
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    if( OUTPUTCONFIG STREQUAL "RELEASE" )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin )
    else()
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_SOURCE_DIR}/bin/${OUTPUTCONFIG} )
    endif()
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

if(MSVC)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS}) 

# configure a header file to pass some of the CMake settings
# to the source code
configure_file ("${CMAKE_SOURCE_DIR}/src/ave_stddev.h.in" "${PROJECT_BINARY_DIR}/ave_stddev.h")
# add the binary tree to the search path for include files
# so that we will find ave_stddev.h
include_directories("${PROJECT_BINARY_DIR}")

add_executable(ave_stddev src/ave_stddev.cpp)


