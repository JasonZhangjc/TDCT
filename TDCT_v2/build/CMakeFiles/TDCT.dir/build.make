# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/js/COMBINE

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/js/COMBINE/build

# Include any dependencies generated for this target.
include CMakeFiles/TDCT.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TDCT.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TDCT.dir/flags.make

CMakeFiles/TDCT.dir/src/delta.cpp.o: CMakeFiles/TDCT.dir/flags.make
CMakeFiles/TDCT.dir/src/delta.cpp.o: ../src/delta.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/js/COMBINE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TDCT.dir/src/delta.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TDCT.dir/src/delta.cpp.o -c /home/js/COMBINE/src/delta.cpp

CMakeFiles/TDCT.dir/src/delta.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TDCT.dir/src/delta.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/js/COMBINE/src/delta.cpp > CMakeFiles/TDCT.dir/src/delta.cpp.i

CMakeFiles/TDCT.dir/src/delta.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TDCT.dir/src/delta.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/js/COMBINE/src/delta.cpp -o CMakeFiles/TDCT.dir/src/delta.cpp.s

CMakeFiles/TDCT.dir/src/delta.cpp.o.requires:

.PHONY : CMakeFiles/TDCT.dir/src/delta.cpp.o.requires

CMakeFiles/TDCT.dir/src/delta.cpp.o.provides: CMakeFiles/TDCT.dir/src/delta.cpp.o.requires
	$(MAKE) -f CMakeFiles/TDCT.dir/build.make CMakeFiles/TDCT.dir/src/delta.cpp.o.provides.build
.PHONY : CMakeFiles/TDCT.dir/src/delta.cpp.o.provides

CMakeFiles/TDCT.dir/src/delta.cpp.o.provides.build: CMakeFiles/TDCT.dir/src/delta.cpp.o


CMakeFiles/TDCT.dir/src/tds.cpp.o: CMakeFiles/TDCT.dir/flags.make
CMakeFiles/TDCT.dir/src/tds.cpp.o: ../src/tds.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/js/COMBINE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TDCT.dir/src/tds.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TDCT.dir/src/tds.cpp.o -c /home/js/COMBINE/src/tds.cpp

CMakeFiles/TDCT.dir/src/tds.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TDCT.dir/src/tds.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/js/COMBINE/src/tds.cpp > CMakeFiles/TDCT.dir/src/tds.cpp.i

CMakeFiles/TDCT.dir/src/tds.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TDCT.dir/src/tds.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/js/COMBINE/src/tds.cpp -o CMakeFiles/TDCT.dir/src/tds.cpp.s

CMakeFiles/TDCT.dir/src/tds.cpp.o.requires:

.PHONY : CMakeFiles/TDCT.dir/src/tds.cpp.o.requires

CMakeFiles/TDCT.dir/src/tds.cpp.o.provides: CMakeFiles/TDCT.dir/src/tds.cpp.o.requires
	$(MAKE) -f CMakeFiles/TDCT.dir/build.make CMakeFiles/TDCT.dir/src/tds.cpp.o.provides.build
.PHONY : CMakeFiles/TDCT.dir/src/tds.cpp.o.provides

CMakeFiles/TDCT.dir/src/tds.cpp.o.provides.build: CMakeFiles/TDCT.dir/src/tds.cpp.o


CMakeFiles/TDCT.dir/src/transition.cpp.o: CMakeFiles/TDCT.dir/flags.make
CMakeFiles/TDCT.dir/src/transition.cpp.o: ../src/transition.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/js/COMBINE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TDCT.dir/src/transition.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TDCT.dir/src/transition.cpp.o -c /home/js/COMBINE/src/transition.cpp

CMakeFiles/TDCT.dir/src/transition.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TDCT.dir/src/transition.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/js/COMBINE/src/transition.cpp > CMakeFiles/TDCT.dir/src/transition.cpp.i

CMakeFiles/TDCT.dir/src/transition.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TDCT.dir/src/transition.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/js/COMBINE/src/transition.cpp -o CMakeFiles/TDCT.dir/src/transition.cpp.s

CMakeFiles/TDCT.dir/src/transition.cpp.o.requires:

.PHONY : CMakeFiles/TDCT.dir/src/transition.cpp.o.requires

CMakeFiles/TDCT.dir/src/transition.cpp.o.provides: CMakeFiles/TDCT.dir/src/transition.cpp.o.requires
	$(MAKE) -f CMakeFiles/TDCT.dir/build.make CMakeFiles/TDCT.dir/src/transition.cpp.o.provides.build
.PHONY : CMakeFiles/TDCT.dir/src/transition.cpp.o.provides

CMakeFiles/TDCT.dir/src/transition.cpp.o.provides.build: CMakeFiles/TDCT.dir/src/transition.cpp.o


CMakeFiles/TDCT.dir/src/io.cpp.o: CMakeFiles/TDCT.dir/flags.make
CMakeFiles/TDCT.dir/src/io.cpp.o: ../src/io.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/js/COMBINE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TDCT.dir/src/io.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TDCT.dir/src/io.cpp.o -c /home/js/COMBINE/src/io.cpp

CMakeFiles/TDCT.dir/src/io.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TDCT.dir/src/io.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/js/COMBINE/src/io.cpp > CMakeFiles/TDCT.dir/src/io.cpp.i

CMakeFiles/TDCT.dir/src/io.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TDCT.dir/src/io.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/js/COMBINE/src/io.cpp -o CMakeFiles/TDCT.dir/src/io.cpp.s

CMakeFiles/TDCT.dir/src/io.cpp.o.requires:

.PHONY : CMakeFiles/TDCT.dir/src/io.cpp.o.requires

CMakeFiles/TDCT.dir/src/io.cpp.o.provides: CMakeFiles/TDCT.dir/src/io.cpp.o.requires
	$(MAKE) -f CMakeFiles/TDCT.dir/build.make CMakeFiles/TDCT.dir/src/io.cpp.o.provides.build
.PHONY : CMakeFiles/TDCT.dir/src/io.cpp.o.provides

CMakeFiles/TDCT.dir/src/io.cpp.o.provides.build: CMakeFiles/TDCT.dir/src/io.cpp.o


CMakeFiles/TDCT.dir/src/event.cpp.o: CMakeFiles/TDCT.dir/flags.make
CMakeFiles/TDCT.dir/src/event.cpp.o: ../src/event.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/js/COMBINE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/TDCT.dir/src/event.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TDCT.dir/src/event.cpp.o -c /home/js/COMBINE/src/event.cpp

CMakeFiles/TDCT.dir/src/event.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TDCT.dir/src/event.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/js/COMBINE/src/event.cpp > CMakeFiles/TDCT.dir/src/event.cpp.i

CMakeFiles/TDCT.dir/src/event.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TDCT.dir/src/event.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/js/COMBINE/src/event.cpp -o CMakeFiles/TDCT.dir/src/event.cpp.s

CMakeFiles/TDCT.dir/src/event.cpp.o.requires:

.PHONY : CMakeFiles/TDCT.dir/src/event.cpp.o.requires

CMakeFiles/TDCT.dir/src/event.cpp.o.provides: CMakeFiles/TDCT.dir/src/event.cpp.o.requires
	$(MAKE) -f CMakeFiles/TDCT.dir/build.make CMakeFiles/TDCT.dir/src/event.cpp.o.provides.build
.PHONY : CMakeFiles/TDCT.dir/src/event.cpp.o.provides

CMakeFiles/TDCT.dir/src/event.cpp.o.provides.build: CMakeFiles/TDCT.dir/src/event.cpp.o


CMakeFiles/TDCT.dir/src/main.cpp.o: CMakeFiles/TDCT.dir/flags.make
CMakeFiles/TDCT.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/js/COMBINE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/TDCT.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TDCT.dir/src/main.cpp.o -c /home/js/COMBINE/src/main.cpp

CMakeFiles/TDCT.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TDCT.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/js/COMBINE/src/main.cpp > CMakeFiles/TDCT.dir/src/main.cpp.i

CMakeFiles/TDCT.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TDCT.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/js/COMBINE/src/main.cpp -o CMakeFiles/TDCT.dir/src/main.cpp.s

CMakeFiles/TDCT.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/TDCT.dir/src/main.cpp.o.requires

CMakeFiles/TDCT.dir/src/main.cpp.o.provides: CMakeFiles/TDCT.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/TDCT.dir/build.make CMakeFiles/TDCT.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/TDCT.dir/src/main.cpp.o.provides

CMakeFiles/TDCT.dir/src/main.cpp.o.provides.build: CMakeFiles/TDCT.dir/src/main.cpp.o


CMakeFiles/TDCT.dir/src/des.cpp.o: CMakeFiles/TDCT.dir/flags.make
CMakeFiles/TDCT.dir/src/des.cpp.o: ../src/des.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/js/COMBINE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/TDCT.dir/src/des.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TDCT.dir/src/des.cpp.o -c /home/js/COMBINE/src/des.cpp

CMakeFiles/TDCT.dir/src/des.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TDCT.dir/src/des.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/js/COMBINE/src/des.cpp > CMakeFiles/TDCT.dir/src/des.cpp.i

CMakeFiles/TDCT.dir/src/des.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TDCT.dir/src/des.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/js/COMBINE/src/des.cpp -o CMakeFiles/TDCT.dir/src/des.cpp.s

CMakeFiles/TDCT.dir/src/des.cpp.o.requires:

.PHONY : CMakeFiles/TDCT.dir/src/des.cpp.o.requires

CMakeFiles/TDCT.dir/src/des.cpp.o.provides: CMakeFiles/TDCT.dir/src/des.cpp.o.requires
	$(MAKE) -f CMakeFiles/TDCT.dir/build.make CMakeFiles/TDCT.dir/src/des.cpp.o.provides.build
.PHONY : CMakeFiles/TDCT.dir/src/des.cpp.o.provides

CMakeFiles/TDCT.dir/src/des.cpp.o.provides.build: CMakeFiles/TDCT.dir/src/des.cpp.o


CMakeFiles/TDCT.dir/src/spec.cpp.o: CMakeFiles/TDCT.dir/flags.make
CMakeFiles/TDCT.dir/src/spec.cpp.o: ../src/spec.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/js/COMBINE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/TDCT.dir/src/spec.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TDCT.dir/src/spec.cpp.o -c /home/js/COMBINE/src/spec.cpp

CMakeFiles/TDCT.dir/src/spec.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TDCT.dir/src/spec.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/js/COMBINE/src/spec.cpp > CMakeFiles/TDCT.dir/src/spec.cpp.i

CMakeFiles/TDCT.dir/src/spec.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TDCT.dir/src/spec.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/js/COMBINE/src/spec.cpp -o CMakeFiles/TDCT.dir/src/spec.cpp.s

CMakeFiles/TDCT.dir/src/spec.cpp.o.requires:

.PHONY : CMakeFiles/TDCT.dir/src/spec.cpp.o.requires

CMakeFiles/TDCT.dir/src/spec.cpp.o.provides: CMakeFiles/TDCT.dir/src/spec.cpp.o.requires
	$(MAKE) -f CMakeFiles/TDCT.dir/build.make CMakeFiles/TDCT.dir/src/spec.cpp.o.provides.build
.PHONY : CMakeFiles/TDCT.dir/src/spec.cpp.o.provides

CMakeFiles/TDCT.dir/src/spec.cpp.o.provides.build: CMakeFiles/TDCT.dir/src/spec.cpp.o


# Object files for target TDCT
TDCT_OBJECTS = \
"CMakeFiles/TDCT.dir/src/delta.cpp.o" \
"CMakeFiles/TDCT.dir/src/tds.cpp.o" \
"CMakeFiles/TDCT.dir/src/transition.cpp.o" \
"CMakeFiles/TDCT.dir/src/io.cpp.o" \
"CMakeFiles/TDCT.dir/src/event.cpp.o" \
"CMakeFiles/TDCT.dir/src/main.cpp.o" \
"CMakeFiles/TDCT.dir/src/des.cpp.o" \
"CMakeFiles/TDCT.dir/src/spec.cpp.o"

# External object files for target TDCT
TDCT_EXTERNAL_OBJECTS =

TDCT: CMakeFiles/TDCT.dir/src/delta.cpp.o
TDCT: CMakeFiles/TDCT.dir/src/tds.cpp.o
TDCT: CMakeFiles/TDCT.dir/src/transition.cpp.o
TDCT: CMakeFiles/TDCT.dir/src/io.cpp.o
TDCT: CMakeFiles/TDCT.dir/src/event.cpp.o
TDCT: CMakeFiles/TDCT.dir/src/main.cpp.o
TDCT: CMakeFiles/TDCT.dir/src/des.cpp.o
TDCT: CMakeFiles/TDCT.dir/src/spec.cpp.o
TDCT: CMakeFiles/TDCT.dir/build.make
TDCT: /usr/local/lib/libbdd.so.0
TDCT: CMakeFiles/TDCT.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/js/COMBINE/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable TDCT"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TDCT.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TDCT.dir/build: TDCT

.PHONY : CMakeFiles/TDCT.dir/build

CMakeFiles/TDCT.dir/requires: CMakeFiles/TDCT.dir/src/delta.cpp.o.requires
CMakeFiles/TDCT.dir/requires: CMakeFiles/TDCT.dir/src/tds.cpp.o.requires
CMakeFiles/TDCT.dir/requires: CMakeFiles/TDCT.dir/src/transition.cpp.o.requires
CMakeFiles/TDCT.dir/requires: CMakeFiles/TDCT.dir/src/io.cpp.o.requires
CMakeFiles/TDCT.dir/requires: CMakeFiles/TDCT.dir/src/event.cpp.o.requires
CMakeFiles/TDCT.dir/requires: CMakeFiles/TDCT.dir/src/main.cpp.o.requires
CMakeFiles/TDCT.dir/requires: CMakeFiles/TDCT.dir/src/des.cpp.o.requires
CMakeFiles/TDCT.dir/requires: CMakeFiles/TDCT.dir/src/spec.cpp.o.requires

.PHONY : CMakeFiles/TDCT.dir/requires

CMakeFiles/TDCT.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TDCT.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TDCT.dir/clean

CMakeFiles/TDCT.dir/depend:
	cd /home/js/COMBINE/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/js/COMBINE /home/js/COMBINE /home/js/COMBINE/build /home/js/COMBINE/build /home/js/COMBINE/build/CMakeFiles/TDCT.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TDCT.dir/depend

