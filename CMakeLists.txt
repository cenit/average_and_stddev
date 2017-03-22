cmake_minimum_required (VERSION 3.1)
project (average_and_stddev)
set (CMAKE_CXX_STANDARD 11)

set (MAJOR_VERSION 1)
set (MINOR_VERSION 2)

add_definitions(-D_SCL_SECURE_NO_WARNINGS)
find_package(Boost)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    
    # configure a header file to pass some of the CMake settings
    # to the source code
    configure_file ("${CMAKE_SOURCE_DIR}/src/ave_stddev.h.in" "${PROJECT_BINARY_DIR}/ave_stddev.h")
    # add the binary tree to the search path for include files
    # so that we will find ave_stddev.h
    include_directories("${PROJECT_BINARY_DIR}")
    
    add_executable(ave_stddev src/ave_stddev.cpp)
    install (TARGETS ave_stddev DESTINATION ${CMAKE_SOURCE_DIR}/bin/)
endif()
