# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mwinter/projects/minishell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mwinter/projects/minishell/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/minishell1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/minishell1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/minishell1.dir/flags.make

CMakeFiles/minishell1.dir/tests/test_signals.c.o: CMakeFiles/minishell1.dir/flags.make
CMakeFiles/minishell1.dir/tests/test_signals.c.o: ../tests/test_signals.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mwinter/projects/minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/minishell1.dir/tests/test_signals.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/minishell1.dir/tests/test_signals.c.o   -c /Users/mwinter/projects/minishell/tests/test_signals.c

CMakeFiles/minishell1.dir/tests/test_signals.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/minishell1.dir/tests/test_signals.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/mwinter/projects/minishell/tests/test_signals.c > CMakeFiles/minishell1.dir/tests/test_signals.c.i

CMakeFiles/minishell1.dir/tests/test_signals.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/minishell1.dir/tests/test_signals.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/mwinter/projects/minishell/tests/test_signals.c -o CMakeFiles/minishell1.dir/tests/test_signals.c.s

# Object files for target minishell1
minishell1_OBJECTS = \
"CMakeFiles/minishell1.dir/tests/test_signals.c.o"

# External object files for target minishell1
minishell1_EXTERNAL_OBJECTS =

minishell1: CMakeFiles/minishell1.dir/tests/test_signals.c.o
minishell1: CMakeFiles/minishell1.dir/build.make
minishell1: CMakeFiles/minishell1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mwinter/projects/minishell/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable minishell1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minishell1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/minishell1.dir/build: minishell1

.PHONY : CMakeFiles/minishell1.dir/build

CMakeFiles/minishell1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/minishell1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/minishell1.dir/clean

CMakeFiles/minishell1.dir/depend:
	cd /Users/mwinter/projects/minishell/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mwinter/projects/minishell /Users/mwinter/projects/minishell /Users/mwinter/projects/minishell/cmake-build-debug /Users/mwinter/projects/minishell/cmake-build-debug /Users/mwinter/projects/minishell/cmake-build-debug/CMakeFiles/minishell1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/minishell1.dir/depend

