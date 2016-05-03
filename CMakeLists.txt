cmake_minimum_required (VERSION 2.6)
project (libOpenCL_loader)
# The version number.
set (clloader_VERSION_MAJOR 1)
set (clloader_VERSION_MINOR 0)

option( BUILD_TESTS "Build test program." ON )

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

include_directories("${PROJECT_SOURCE_DIR}/include/")
include(CMakeParseArguments)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
message(STATUS "Project source dir = ${PROJECT_SOURCE_DIR}")
message(STATUS "Project build dir = ${PROJECT_BINARY_DIR}")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wall")
endif()

add_definitions(-DCL_USE_DEPRECATED_OPENCL_1_1_APIS)

add_subdirectory(src)
if( BUILD_TESTS )
  add_subdirectory(test)
endif( BUILD_TESTS )
