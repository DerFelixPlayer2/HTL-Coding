# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung 1/TOPO"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung 1/TOPO/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/TOPO.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TOPO.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TOPO.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TOPO.dir/flags.make

CMakeFiles/TOPO.dir/main.cpp.o: CMakeFiles/TOPO.dir/flags.make
CMakeFiles/TOPO.dir/main.cpp.o: /mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung\ 1/TOPO/main.cpp
CMakeFiles/TOPO.dir/main.cpp.o: CMakeFiles/TOPO.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung 1/TOPO/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TOPO.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/TOPO.dir/main.cpp.o -MF CMakeFiles/TOPO.dir/main.cpp.o.d -o CMakeFiles/TOPO.dir/main.cpp.o -c "/mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung 1/TOPO/main.cpp"

CMakeFiles/TOPO.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TOPO.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung 1/TOPO/main.cpp" > CMakeFiles/TOPO.dir/main.cpp.i

CMakeFiles/TOPO.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TOPO.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung 1/TOPO/main.cpp" -o CMakeFiles/TOPO.dir/main.cpp.s

# Object files for target TOPO
TOPO_OBJECTS = \
"CMakeFiles/TOPO.dir/main.cpp.o"

# External object files for target TOPO
TOPO_EXTERNAL_OBJECTS =

TOPO: CMakeFiles/TOPO.dir/main.cpp.o
TOPO: CMakeFiles/TOPO.dir/build.make
TOPO: CMakeFiles/TOPO.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung 1/TOPO/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable TOPO"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TOPO.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TOPO.dir/build: TOPO
.PHONY : CMakeFiles/TOPO.dir/build

CMakeFiles/TOPO.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TOPO.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TOPO.dir/clean

CMakeFiles/TOPO.dir/depend:
	cd "/mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung 1/TOPO/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung 1/TOPO" "/mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung 1/TOPO" "/mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung 1/TOPO/cmake-build-debug" "/mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung 1/TOPO/cmake-build-debug" "/mnt/c/Users/felix/Desktop/CodeProjects/IOI/2022/Vorbereitung 1/TOPO/cmake-build-debug/CMakeFiles/TOPO.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/TOPO.dir/depend

