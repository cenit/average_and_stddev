cmake_minimum_required (VERSION 2.6)
project (average_and_stddev)
set (MAJOR_VERSION 1)
set (MINOR_VERSION 0)
# configure a header file to pass some of the CMake settings
# to the source code
configure_file ("src/ave_stddev.h.in" "${PROJECT_BINARY_DIR}/ave_stddev.h")
# add the binary tree to the search path for include files
# so that we will find ave_stddev.h
include_directories("${PROJECT_BINARY_DIR}")

add_executable(ave_stddev src/ave_stddev.cpp)
