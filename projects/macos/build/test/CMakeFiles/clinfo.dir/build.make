# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.13.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.13.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/guohuiwang/dev/mine/libOpenCL-loader

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/guohuiwang/dev/mine/libOpenCL-loader/projects/macos/build

# Include any dependencies generated for this target.
include test/CMakeFiles/clinfo.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/clinfo.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/clinfo.dir/flags.make

test/CMakeFiles/clinfo.dir/clinfo.cpp.o: test/CMakeFiles/clinfo.dir/flags.make
test/CMakeFiles/clinfo.dir/clinfo.cpp.o: ../../../test/clinfo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/guohuiwang/dev/mine/libOpenCL-loader/projects/macos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/clinfo.dir/clinfo.cpp.o"
	cd /Users/guohuiwang/dev/mine/libOpenCL-loader/projects/macos/build/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/clinfo.dir/clinfo.cpp.o -c /Users/guohuiwang/dev/mine/libOpenCL-loader/test/clinfo.cpp

test/CMakeFiles/clinfo.dir/clinfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/clinfo.dir/clinfo.cpp.i"
	cd /Users/guohuiwang/dev/mine/libOpenCL-loader/projects/macos/build/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/guohuiwang/dev/mine/libOpenCL-loader/test/clinfo.cpp > CMakeFiles/clinfo.dir/clinfo.cpp.i

test/CMakeFiles/clinfo.dir/clinfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/clinfo.dir/clinfo.cpp.s"
	cd /Users/guohuiwang/dev/mine/libOpenCL-loader/projects/macos/build/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/guohuiwang/dev/mine/libOpenCL-loader/test/clinfo.cpp -o CMakeFiles/clinfo.dir/clinfo.cpp.s

# Object files for target clinfo
clinfo_OBJECTS = \
"CMakeFiles/clinfo.dir/clinfo.cpp.o"

# External object files for target clinfo
clinfo_EXTERNAL_OBJECTS =

../../../bin/clinfo: test/CMakeFiles/clinfo.dir/clinfo.cpp.o
../../../bin/clinfo: test/CMakeFiles/clinfo.dir/build.make
../../../bin/clinfo: ../../../lib/libopencl_loader.dylib
../../../bin/clinfo: test/CMakeFiles/clinfo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/guohuiwang/dev/mine/libOpenCL-loader/projects/macos/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../../bin/clinfo"
	cd /Users/guohuiwang/dev/mine/libOpenCL-loader/projects/macos/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/clinfo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/clinfo.dir/build: ../../../bin/clinfo

.PHONY : test/CMakeFiles/clinfo.dir/build

test/CMakeFiles/clinfo.dir/clean:
	cd /Users/guohuiwang/dev/mine/libOpenCL-loader/projects/macos/build/test && $(CMAKE_COMMAND) -P CMakeFiles/clinfo.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/clinfo.dir/clean

test/CMakeFiles/clinfo.dir/depend:
	cd /Users/guohuiwang/dev/mine/libOpenCL-loader/projects/macos/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/guohuiwang/dev/mine/libOpenCL-loader /Users/guohuiwang/dev/mine/libOpenCL-loader/test /Users/guohuiwang/dev/mine/libOpenCL-loader/projects/macos/build /Users/guohuiwang/dev/mine/libOpenCL-loader/projects/macos/build/test /Users/guohuiwang/dev/mine/libOpenCL-loader/projects/macos/build/test/CMakeFiles/clinfo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/clinfo.dir/depend

