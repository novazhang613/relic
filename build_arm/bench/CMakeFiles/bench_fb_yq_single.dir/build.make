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
CMAKE_SOURCE_DIR = /home/yiqun/adi/relic-master-SS

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yiqun/adi/relic-master-SS/build_arm

# Include any dependencies generated for this target.
include bench/CMakeFiles/bench_fb_yq_single.dir/depend.make

# Include the progress variables for this target.
include bench/CMakeFiles/bench_fb_yq_single.dir/progress.make

# Include the compile flags for this target's objects.
include bench/CMakeFiles/bench_fb_yq_single.dir/flags.make

bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj: bench/CMakeFiles/bench_fb_yq_single.dir/flags.make
bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj: ../bench/bench_fb_yq_single.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yiqun/adi/relic-master-SS/build_arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj"
	cd /home/yiqun/adi/relic-master-SS/build_arm/bench && /home/yiqun/tools/gcc-arm-none-eabi-7-2017-q4-major/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj   -c /home/yiqun/adi/relic-master-SS/bench/bench_fb_yq_single.c

bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.i"
	cd /home/yiqun/adi/relic-master-SS/build_arm/bench && /home/yiqun/tools/gcc-arm-none-eabi-7-2017-q4-major/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/yiqun/adi/relic-master-SS/bench/bench_fb_yq_single.c > CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.i

bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.s"
	cd /home/yiqun/adi/relic-master-SS/build_arm/bench && /home/yiqun/tools/gcc-arm-none-eabi-7-2017-q4-major/bin/arm-none-eabi-gcc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/yiqun/adi/relic-master-SS/bench/bench_fb_yq_single.c -o CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.s

bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj.requires:

.PHONY : bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj.requires

bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj.provides: bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj.requires
	$(MAKE) -f bench/CMakeFiles/bench_fb_yq_single.dir/build.make bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj.provides.build
.PHONY : bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj.provides

bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj.provides.build: bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj


# Object files for target bench_fb_yq_single
bench_fb_yq_single_OBJECTS = \
"CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj"

# External object files for target bench_fb_yq_single
bench_fb_yq_single_EXTERNAL_OBJECTS =

bin/bench_fb_yq_single: bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj
bin/bench_fb_yq_single: bench/CMakeFiles/bench_fb_yq_single.dir/build.make
bin/bench_fb_yq_single: lib/librelic_s.a
bin/bench_fb_yq_single: bench/CMakeFiles/bench_fb_yq_single.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yiqun/adi/relic-master-SS/build_arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ../bin/bench_fb_yq_single"
	cd /home/yiqun/adi/relic-master-SS/build_arm/bench && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bench_fb_yq_single.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bench/CMakeFiles/bench_fb_yq_single.dir/build: bin/bench_fb_yq_single

.PHONY : bench/CMakeFiles/bench_fb_yq_single.dir/build

bench/CMakeFiles/bench_fb_yq_single.dir/requires: bench/CMakeFiles/bench_fb_yq_single.dir/bench_fb_yq_single.c.obj.requires

.PHONY : bench/CMakeFiles/bench_fb_yq_single.dir/requires

bench/CMakeFiles/bench_fb_yq_single.dir/clean:
	cd /home/yiqun/adi/relic-master-SS/build_arm/bench && $(CMAKE_COMMAND) -P CMakeFiles/bench_fb_yq_single.dir/cmake_clean.cmake
.PHONY : bench/CMakeFiles/bench_fb_yq_single.dir/clean

bench/CMakeFiles/bench_fb_yq_single.dir/depend:
	cd /home/yiqun/adi/relic-master-SS/build_arm && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yiqun/adi/relic-master-SS /home/yiqun/adi/relic-master-SS/bench /home/yiqun/adi/relic-master-SS/build_arm /home/yiqun/adi/relic-master-SS/build_arm/bench /home/yiqun/adi/relic-master-SS/build_arm/bench/CMakeFiles/bench_fb_yq_single.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bench/CMakeFiles/bench_fb_yq_single.dir/depend

