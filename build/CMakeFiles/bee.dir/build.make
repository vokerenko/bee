# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/oleh/bee

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/oleh/bee/build

# Include any dependencies generated for this target.
include CMakeFiles/bee.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bee.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bee.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bee.dir/flags.make

CMakeFiles/bee.dir/src/main.c.o: CMakeFiles/bee.dir/flags.make
CMakeFiles/bee.dir/src/main.c.o: /home/oleh/bee/src/main.c
CMakeFiles/bee.dir/src/main.c.o: CMakeFiles/bee.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/oleh/bee/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/bee.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/bee.dir/src/main.c.o -MF CMakeFiles/bee.dir/src/main.c.o.d -o CMakeFiles/bee.dir/src/main.c.o -c /home/oleh/bee/src/main.c

CMakeFiles/bee.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/bee.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/oleh/bee/src/main.c > CMakeFiles/bee.dir/src/main.c.i

CMakeFiles/bee.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/bee.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/oleh/bee/src/main.c -o CMakeFiles/bee.dir/src/main.c.s

# Object files for target bee
bee_OBJECTS = \
"CMakeFiles/bee.dir/src/main.c.o"

# External object files for target bee
bee_EXTERNAL_OBJECTS =

/home/oleh/bee/bee: CMakeFiles/bee.dir/src/main.c.o
/home/oleh/bee/bee: CMakeFiles/bee.dir/build.make
/home/oleh/bee/bee: /usr/lib/x86_64-linux-gnu/libSDL2.so
/home/oleh/bee/bee: CMakeFiles/bee.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/oleh/bee/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable /home/oleh/bee/bee"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bee.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bee.dir/build: /home/oleh/bee/bee
.PHONY : CMakeFiles/bee.dir/build

CMakeFiles/bee.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/bee.dir/cmake_clean.cmake
.PHONY : CMakeFiles/bee.dir/clean

CMakeFiles/bee.dir/depend:
	cd /home/oleh/bee/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/oleh/bee /home/oleh/bee /home/oleh/bee/build /home/oleh/bee/build /home/oleh/bee/build/CMakeFiles/bee.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/bee.dir/depend

