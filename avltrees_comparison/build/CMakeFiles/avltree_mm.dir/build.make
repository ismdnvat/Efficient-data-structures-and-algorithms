# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tameris/6sem/isamidinova-EDSA/avltrees_comparison

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tameris/6sem/isamidinova-EDSA/avltrees_comparison/build

# Include any dependencies generated for this target.
include CMakeFiles/avltree_mm.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/avltree_mm.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/avltree_mm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/avltree_mm.dir/flags.make

CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.o: CMakeFiles/avltree_mm.dir/flags.make
CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.o: ../avltree_mm/avltree_test.cpp
CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.o: CMakeFiles/avltree_mm.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tameris/6sem/isamidinova-EDSA/avltrees_comparison/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.o -MF CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.o.d -o CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.o -c /home/tameris/6sem/isamidinova-EDSA/avltrees_comparison/avltree_mm/avltree_test.cpp

CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tameris/6sem/isamidinova-EDSA/avltrees_comparison/avltree_mm/avltree_test.cpp > CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.i

CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tameris/6sem/isamidinova-EDSA/avltrees_comparison/avltree_mm/avltree_test.cpp -o CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.s

# Object files for target avltree_mm
avltree_mm_OBJECTS = \
"CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.o"

# External object files for target avltree_mm
avltree_mm_EXTERNAL_OBJECTS =

bin/avltree_mm: CMakeFiles/avltree_mm.dir/avltree_mm/avltree_test.cpp.o
bin/avltree_mm: CMakeFiles/avltree_mm.dir/build.make
bin/avltree_mm: CMakeFiles/avltree_mm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tameris/6sem/isamidinova-EDSA/avltrees_comparison/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/avltree_mm"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/avltree_mm.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/avltree_mm.dir/build: bin/avltree_mm
.PHONY : CMakeFiles/avltree_mm.dir/build

CMakeFiles/avltree_mm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/avltree_mm.dir/cmake_clean.cmake
.PHONY : CMakeFiles/avltree_mm.dir/clean

CMakeFiles/avltree_mm.dir/depend:
	cd /home/tameris/6sem/isamidinova-EDSA/avltrees_comparison/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tameris/6sem/isamidinova-EDSA/avltrees_comparison /home/tameris/6sem/isamidinova-EDSA/avltrees_comparison /home/tameris/6sem/isamidinova-EDSA/avltrees_comparison/build /home/tameris/6sem/isamidinova-EDSA/avltrees_comparison/build /home/tameris/6sem/isamidinova-EDSA/avltrees_comparison/build/CMakeFiles/avltree_mm.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/avltree_mm.dir/depend

