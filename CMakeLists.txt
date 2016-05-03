cmake_minimum_required (VERSION 2.6)
project (libOpenCL_loader)
# The version number.
set (clloader_VERSION_MAJOR 1)
set (clloader_VERSION_MINOR 0)

option( BUILD_TESTS "Build test program." ON )
option( BUILD_SHARED_LIBRARY "Shared library, rather than static library." ON )

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

include_directories("${PROJECT_SOURCE_DIR}/include/")
include(CMakeParseArguments)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
message(STATUS "Project source dir = ${PROJECT_SOURCE_DIR}")
message(STATUS "Project build dir = ${CMAKE_BINARY_DIR}")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall")
endif()

add_definitions(-DCL_USE_DEPRECATED_OPENCL_1_1_APIS)

if( NOT BUILD_SHARED_LIBRARY )
  add_definitions(-Dcl_loader_static)
endif()

add_subdirectory(src)
if( BUILD_TESTS )
  add_subdirectory(test)
endif( BUILD_TESTS )
