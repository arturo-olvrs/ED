# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /snap/clion/250/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/250/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/crop.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/crop.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/crop.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/crop.dir/flags.make

CMakeFiles/crop.dir/estudiante/src/crop.cpp.o: CMakeFiles/crop.dir/flags.make
CMakeFiles/crop.dir/estudiante/src/crop.cpp.o: /home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo/estudiante/src/crop.cpp
CMakeFiles/crop.dir/estudiante/src/crop.cpp.o: CMakeFiles/crop.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/crop.dir/estudiante/src/crop.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/crop.dir/estudiante/src/crop.cpp.o -MF CMakeFiles/crop.dir/estudiante/src/crop.cpp.o.d -o CMakeFiles/crop.dir/estudiante/src/crop.cpp.o -c /home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo/estudiante/src/crop.cpp

CMakeFiles/crop.dir/estudiante/src/crop.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/crop.dir/estudiante/src/crop.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo/estudiante/src/crop.cpp > CMakeFiles/crop.dir/estudiante/src/crop.cpp.i

CMakeFiles/crop.dir/estudiante/src/crop.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/crop.dir/estudiante/src/crop.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo/estudiante/src/crop.cpp -o CMakeFiles/crop.dir/estudiante/src/crop.cpp.s

# Object files for target crop
crop_OBJECTS = \
"CMakeFiles/crop.dir/estudiante/src/crop.cpp.o"

# External object files for target crop
crop_EXTERNAL_OBJECTS =

crop: CMakeFiles/crop.dir/estudiante/src/crop.cpp.o
crop: CMakeFiles/crop.dir/build.make
crop: libimage.a
crop: CMakeFiles/crop.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable crop"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crop.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/crop.dir/build: crop
.PHONY : CMakeFiles/crop.dir/build

CMakeFiles/crop.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/crop.dir/cmake_clean.cmake
.PHONY : CMakeFiles/crop.dir/clean

CMakeFiles/crop.dir/depend:
	cd /home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo /home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo /home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo/cmake-build-debug /home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo/cmake-build-debug /home/arturoolvrs/Desktop/practicas_ED/TDA_imagen/codigo/cmake-build-debug/CMakeFiles/crop.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/crop.dir/depend

