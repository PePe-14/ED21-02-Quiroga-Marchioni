# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\jmarc\Documents\GitHub\ED21-02-Quiroga-Marchioni\Tarea1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\jmarc\Documents\GitHub\ED21-02-Quiroga-Marchioni\Tarea1\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Tarea1.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Tarea1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Tarea1.dir/flags.make

CMakeFiles/Tarea1.dir/main.cpp.obj: CMakeFiles/Tarea1.dir/flags.make
CMakeFiles/Tarea1.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\jmarc\Documents\GitHub\ED21-02-Quiroga-Marchioni\Tarea1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Tarea1.dir/main.cpp.obj"
	C:\MinGW64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Tarea1.dir\main.cpp.obj -c C:\Users\jmarc\Documents\GitHub\ED21-02-Quiroga-Marchioni\Tarea1\main.cpp

CMakeFiles/Tarea1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Tarea1.dir/main.cpp.i"
	C:\MinGW64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\jmarc\Documents\GitHub\ED21-02-Quiroga-Marchioni\Tarea1\main.cpp > CMakeFiles\Tarea1.dir\main.cpp.i

CMakeFiles/Tarea1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Tarea1.dir/main.cpp.s"
	C:\MinGW64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\jmarc\Documents\GitHub\ED21-02-Quiroga-Marchioni\Tarea1\main.cpp -o CMakeFiles\Tarea1.dir\main.cpp.s

# Object files for target Tarea1
Tarea1_OBJECTS = \
"CMakeFiles/Tarea1.dir/main.cpp.obj"

# External object files for target Tarea1
Tarea1_EXTERNAL_OBJECTS =

Tarea1.exe: CMakeFiles/Tarea1.dir/main.cpp.obj
Tarea1.exe: CMakeFiles/Tarea1.dir/build.make
Tarea1.exe: CMakeFiles/Tarea1.dir/linklibs.rsp
Tarea1.exe: CMakeFiles/Tarea1.dir/objects1.rsp
Tarea1.exe: CMakeFiles/Tarea1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\jmarc\Documents\GitHub\ED21-02-Quiroga-Marchioni\Tarea1\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Tarea1.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Tarea1.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Tarea1.dir/build: Tarea1.exe
.PHONY : CMakeFiles/Tarea1.dir/build

CMakeFiles/Tarea1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Tarea1.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Tarea1.dir/clean

CMakeFiles/Tarea1.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\jmarc\Documents\GitHub\ED21-02-Quiroga-Marchioni\Tarea1 C:\Users\jmarc\Documents\GitHub\ED21-02-Quiroga-Marchioni\Tarea1 C:\Users\jmarc\Documents\GitHub\ED21-02-Quiroga-Marchioni\Tarea1\cmake-build-debug C:\Users\jmarc\Documents\GitHub\ED21-02-Quiroga-Marchioni\Tarea1\cmake-build-debug C:\Users\jmarc\Documents\GitHub\ED21-02-Quiroga-Marchioni\Tarea1\cmake-build-debug\CMakeFiles\Tarea1.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Tarea1.dir/depend

