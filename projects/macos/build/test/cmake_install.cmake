# Install script for directory: /Users/guohuiwang/dev/mine/libOpenCL-loader/test

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/test_cl_h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/guohuiwang/dev/mine/libOpenCL-loader/bin" TYPE EXECUTABLE FILES "/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/test_cl_h")
  if(EXISTS "$ENV{DESTDIR}/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/test_cl_h" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/test_cl_h")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/guohuiwang/dev/mine/libOpenCL-loader/lib"
      "$ENV{DESTDIR}/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/test_cl_h")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/test_cl_h")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/test_cl_hpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/guohuiwang/dev/mine/libOpenCL-loader/bin" TYPE EXECUTABLE FILES "/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/test_cl_hpp")
  if(EXISTS "$ENV{DESTDIR}/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/test_cl_hpp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/test_cl_hpp")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/guohuiwang/dev/mine/libOpenCL-loader/lib"
      "$ENV{DESTDIR}/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/test_cl_hpp")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/test_cl_hpp")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/clinfo")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/guohuiwang/dev/mine/libOpenCL-loader/bin" TYPE EXECUTABLE FILES "/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/clinfo")
  if(EXISTS "$ENV{DESTDIR}/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/clinfo" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/clinfo")
    execute_process(COMMAND /usr/bin/install_name_tool
      -delete_rpath "/Users/guohuiwang/dev/mine/libOpenCL-loader/lib"
      "$ENV{DESTDIR}/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/clinfo")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}/Users/guohuiwang/dev/mine/libOpenCL-loader/bin/clinfo")
    endif()
  endif()
endif()

