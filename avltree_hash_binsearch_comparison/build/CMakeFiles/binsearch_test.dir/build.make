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
CMAKE_SOURCE_DIR = /home/tameris/isamidinova-EDSA/avltree_hash_binsearch_comparison

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tameris/isamidinova-EDSA/avltree_hash_binsearch_comparison/build

# Include any dependencies generated for this target.
include CMakeFiles/binsearch_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/binsearch_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/binsearch_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/binsearch_test.dir/flags.make

CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.o: CMakeFiles/binsearch_test.dir/flags.make
CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.o: ../binsearch_test/test_binsearch.cpp
CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.o: CMakeFiles/binsearch_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tameris/isamidinova-EDSA/avltree_hash_binsearch_comparison/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.o -MF CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.o.d -o CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.o -c /home/tameris/isamidinova-EDSA/avltree_hash_binsearch_comparison/binsearch_test/test_binsearch.cpp

CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tameris/isamidinova-EDSA/avltree_hash_binsearch_comparison/binsearch_test/test_binsearch.cpp > CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.i

CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tameris/isamidinova-EDSA/avltree_hash_binsearch_comparison/binsearch_test/test_binsearch.cpp -o CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.s

# Object files for target binsearch_test
binsearch_test_OBJECTS = \
"CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.o"

# External object files for target binsearch_test
binsearch_test_EXTERNAL_OBJECTS =

bin/binsearch_test: CMakeFiles/binsearch_test.dir/binsearch_test/test_binsearch.cpp.o
bin/binsearch_test: CMakeFiles/binsearch_test.dir/build.make
bin/binsearch_test: CMakeFiles/binsearch_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tameris/isamidinova-EDSA/avltree_hash_binsearch_comparison/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/binsearch_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/binsearch_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/binsearch_test.dir/build: bin/binsearch_test
.PHONY : CMakeFiles/binsearch_test.dir/build

CMakeFiles/binsearch_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/binsearch_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/binsearch_test.dir/clean

CMakeFiles/binsearch_test.dir/depend:
	cd /home/tameris/isamidinova-EDSA/avltree_hash_binsearch_comparison/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tameris/isamidinova-EDSA/avltree_hash_binsearch_comparison /home/tameris/isamidinova-EDSA/avltree_hash_binsearch_comparison /home/tameris/isamidinova-EDSA/avltree_hash_binsearch_comparison/build /home/tameris/isamidinova-EDSA/avltree_hash_binsearch_comparison/build /home/tameris/isamidinova-EDSA/avltree_hash_binsearch_comparison/build/CMakeFiles/binsearch_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/binsearch_test.dir/depend
