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
CMAKE_SOURCE_DIR = /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/src/h6x_serial_interface/h6x_packet_handler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/build/h6x_packet_handler

# Include any dependencies generated for this target.
include CMakeFiles/h6x_packet_handler.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/h6x_packet_handler.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/h6x_packet_handler.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/h6x_packet_handler.dir/flags.make

CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.o: CMakeFiles/h6x_packet_handler.dir/flags.make
CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.o: /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/src/h6x_serial_interface/h6x_packet_handler/src/crc_handler.cpp
CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.o: CMakeFiles/h6x_packet_handler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/build/h6x_packet_handler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.o -MF CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.o.d -o CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.o -c /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/src/h6x_serial_interface/h6x_packet_handler/src/crc_handler.cpp

CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/src/h6x_serial_interface/h6x_packet_handler/src/crc_handler.cpp > CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.i

CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/src/h6x_serial_interface/h6x_packet_handler/src/crc_handler.cpp -o CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.s

CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.o: CMakeFiles/h6x_packet_handler.dir/flags.make
CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.o: /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/src/h6x_serial_interface/h6x_packet_handler/src/hex_handler.cpp
CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.o: CMakeFiles/h6x_packet_handler.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/build/h6x_packet_handler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.o -MF CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.o.d -o CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.o -c /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/src/h6x_serial_interface/h6x_packet_handler/src/hex_handler.cpp

CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/src/h6x_serial_interface/h6x_packet_handler/src/hex_handler.cpp > CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.i

CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/src/h6x_serial_interface/h6x_packet_handler/src/hex_handler.cpp -o CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.s

# Object files for target h6x_packet_handler
h6x_packet_handler_OBJECTS = \
"CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.o" \
"CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.o"

# External object files for target h6x_packet_handler
h6x_packet_handler_EXTERNAL_OBJECTS =

libh6x_packet_handler.so: CMakeFiles/h6x_packet_handler.dir/src/crc_handler.cpp.o
libh6x_packet_handler.so: CMakeFiles/h6x_packet_handler.dir/src/hex_handler.cpp.o
libh6x_packet_handler.so: CMakeFiles/h6x_packet_handler.dir/build.make
libh6x_packet_handler.so: CMakeFiles/h6x_packet_handler.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/build/h6x_packet_handler/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library libh6x_packet_handler.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/h6x_packet_handler.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/h6x_packet_handler.dir/build: libh6x_packet_handler.so
.PHONY : CMakeFiles/h6x_packet_handler.dir/build

CMakeFiles/h6x_packet_handler.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/h6x_packet_handler.dir/cmake_clean.cmake
.PHONY : CMakeFiles/h6x_packet_handler.dir/clean

CMakeFiles/h6x_packet_handler.dir/depend:
	cd /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/build/h6x_packet_handler && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/src/h6x_serial_interface/h6x_packet_handler /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/src/h6x_serial_interface/h6x_packet_handler /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/build/h6x_packet_handler /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/build/h6x_packet_handler /mnt/c/Users/niino/Desktop/M1/HarvestX/test2/test2/build/h6x_packet_handler/CMakeFiles/h6x_packet_handler.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/h6x_packet_handler.dir/depend
