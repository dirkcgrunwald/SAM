# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/elgood/Code/eclipse/Streaming-c++/SAM

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/elgood/Code/eclipse/Streaming-c++/SAM

# Include any dependencies generated for this target.
include CMakeFiles/TestSlidingWindow.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TestSlidingWindow.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TestSlidingWindow.dir/flags.make

CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o: CMakeFiles/TestSlidingWindow.dir/flags.make
CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o: TestSrc/TestSlidingWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/elgood/Code/eclipse/Streaming-c++/SAM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o -c /Users/elgood/Code/eclipse/Streaming-c++/SAM/TestSrc/TestSlidingWindow.cpp

CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/elgood/Code/eclipse/Streaming-c++/SAM/TestSrc/TestSlidingWindow.cpp > CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.i

CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/elgood/Code/eclipse/Streaming-c++/SAM/TestSrc/TestSlidingWindow.cpp -o CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.s

CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o.requires:

.PHONY : CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o.requires

CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o.provides: CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o.requires
	$(MAKE) -f CMakeFiles/TestSlidingWindow.dir/build.make CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o.provides.build
.PHONY : CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o.provides

CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o.provides.build: CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o


# Object files for target TestSlidingWindow
TestSlidingWindow_OBJECTS = \
"CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o"

# External object files for target TestSlidingWindow
TestSlidingWindow_EXTERNAL_OBJECTS =

tests/TestSlidingWindow: CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o
tests/TestSlidingWindow: CMakeFiles/TestSlidingWindow.dir/build.make
tests/TestSlidingWindow: CMakeFiles/TestSlidingWindow.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/elgood/Code/eclipse/Streaming-c++/SAM/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tests/TestSlidingWindow"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TestSlidingWindow.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TestSlidingWindow.dir/build: tests/TestSlidingWindow

.PHONY : CMakeFiles/TestSlidingWindow.dir/build

CMakeFiles/TestSlidingWindow.dir/requires: CMakeFiles/TestSlidingWindow.dir/TestSrc/TestSlidingWindow.cpp.o.requires

.PHONY : CMakeFiles/TestSlidingWindow.dir/requires

CMakeFiles/TestSlidingWindow.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TestSlidingWindow.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TestSlidingWindow.dir/clean

CMakeFiles/TestSlidingWindow.dir/depend:
	cd /Users/elgood/Code/eclipse/Streaming-c++/SAM && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/elgood/Code/eclipse/Streaming-c++/SAM /Users/elgood/Code/eclipse/Streaming-c++/SAM /Users/elgood/Code/eclipse/Streaming-c++/SAM /Users/elgood/Code/eclipse/Streaming-c++/SAM /Users/elgood/Code/eclipse/Streaming-c++/SAM/CMakeFiles/TestSlidingWindow.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TestSlidingWindow.dir/depend
