# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /root/下载/clion-2018.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /root/下载/clion-2018.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/SatelliteSLAM/tools/c/prepareData

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/SatelliteSLAM/tools/c/prepareData/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/prepareData.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/prepareData.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/prepareData.dir/flags.make

CMakeFiles/prepareData.dir/main.cpp.o: CMakeFiles/prepareData.dir/flags.make
CMakeFiles/prepareData.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/SatelliteSLAM/tools/c/prepareData/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/prepareData.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/prepareData.dir/main.cpp.o -c /root/SatelliteSLAM/tools/c/prepareData/main.cpp

CMakeFiles/prepareData.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prepareData.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/SatelliteSLAM/tools/c/prepareData/main.cpp > CMakeFiles/prepareData.dir/main.cpp.i

CMakeFiles/prepareData.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prepareData.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/SatelliteSLAM/tools/c/prepareData/main.cpp -o CMakeFiles/prepareData.dir/main.cpp.s

CMakeFiles/prepareData.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/prepareData.dir/main.cpp.o.requires

CMakeFiles/prepareData.dir/main.cpp.o.provides: CMakeFiles/prepareData.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/prepareData.dir/build.make CMakeFiles/prepareData.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/prepareData.dir/main.cpp.o.provides

CMakeFiles/prepareData.dir/main.cpp.o.provides.build: CMakeFiles/prepareData.dir/main.cpp.o


CMakeFiles/prepareData.dir/tinyxml2.cpp.o: CMakeFiles/prepareData.dir/flags.make
CMakeFiles/prepareData.dir/tinyxml2.cpp.o: ../tinyxml2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/SatelliteSLAM/tools/c/prepareData/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/prepareData.dir/tinyxml2.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/prepareData.dir/tinyxml2.cpp.o -c /root/SatelliteSLAM/tools/c/prepareData/tinyxml2.cpp

CMakeFiles/prepareData.dir/tinyxml2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prepareData.dir/tinyxml2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/SatelliteSLAM/tools/c/prepareData/tinyxml2.cpp > CMakeFiles/prepareData.dir/tinyxml2.cpp.i

CMakeFiles/prepareData.dir/tinyxml2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prepareData.dir/tinyxml2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/SatelliteSLAM/tools/c/prepareData/tinyxml2.cpp -o CMakeFiles/prepareData.dir/tinyxml2.cpp.s

CMakeFiles/prepareData.dir/tinyxml2.cpp.o.requires:

.PHONY : CMakeFiles/prepareData.dir/tinyxml2.cpp.o.requires

CMakeFiles/prepareData.dir/tinyxml2.cpp.o.provides: CMakeFiles/prepareData.dir/tinyxml2.cpp.o.requires
	$(MAKE) -f CMakeFiles/prepareData.dir/build.make CMakeFiles/prepareData.dir/tinyxml2.cpp.o.provides.build
.PHONY : CMakeFiles/prepareData.dir/tinyxml2.cpp.o.provides

CMakeFiles/prepareData.dir/tinyxml2.cpp.o.provides.build: CMakeFiles/prepareData.dir/tinyxml2.cpp.o


CMakeFiles/prepareData.dir/BasicFunc.cpp.o: CMakeFiles/prepareData.dir/flags.make
CMakeFiles/prepareData.dir/BasicFunc.cpp.o: ../BasicFunc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/SatelliteSLAM/tools/c/prepareData/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/prepareData.dir/BasicFunc.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/prepareData.dir/BasicFunc.cpp.o -c /root/SatelliteSLAM/tools/c/prepareData/BasicFunc.cpp

CMakeFiles/prepareData.dir/BasicFunc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prepareData.dir/BasicFunc.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/SatelliteSLAM/tools/c/prepareData/BasicFunc.cpp > CMakeFiles/prepareData.dir/BasicFunc.cpp.i

CMakeFiles/prepareData.dir/BasicFunc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prepareData.dir/BasicFunc.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/SatelliteSLAM/tools/c/prepareData/BasicFunc.cpp -o CMakeFiles/prepareData.dir/BasicFunc.cpp.s

CMakeFiles/prepareData.dir/BasicFunc.cpp.o.requires:

.PHONY : CMakeFiles/prepareData.dir/BasicFunc.cpp.o.requires

CMakeFiles/prepareData.dir/BasicFunc.cpp.o.provides: CMakeFiles/prepareData.dir/BasicFunc.cpp.o.requires
	$(MAKE) -f CMakeFiles/prepareData.dir/build.make CMakeFiles/prepareData.dir/BasicFunc.cpp.o.provides.build
.PHONY : CMakeFiles/prepareData.dir/BasicFunc.cpp.o.provides

CMakeFiles/prepareData.dir/BasicFunc.cpp.o.provides.build: CMakeFiles/prepareData.dir/BasicFunc.cpp.o


CMakeFiles/prepareData.dir/DataProcess.cpp.o: CMakeFiles/prepareData.dir/flags.make
CMakeFiles/prepareData.dir/DataProcess.cpp.o: ../DataProcess.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/SatelliteSLAM/tools/c/prepareData/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/prepareData.dir/DataProcess.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/prepareData.dir/DataProcess.cpp.o -c /root/SatelliteSLAM/tools/c/prepareData/DataProcess.cpp

CMakeFiles/prepareData.dir/DataProcess.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prepareData.dir/DataProcess.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/SatelliteSLAM/tools/c/prepareData/DataProcess.cpp > CMakeFiles/prepareData.dir/DataProcess.cpp.i

CMakeFiles/prepareData.dir/DataProcess.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prepareData.dir/DataProcess.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/SatelliteSLAM/tools/c/prepareData/DataProcess.cpp -o CMakeFiles/prepareData.dir/DataProcess.cpp.s

CMakeFiles/prepareData.dir/DataProcess.cpp.o.requires:

.PHONY : CMakeFiles/prepareData.dir/DataProcess.cpp.o.requires

CMakeFiles/prepareData.dir/DataProcess.cpp.o.provides: CMakeFiles/prepareData.dir/DataProcess.cpp.o.requires
	$(MAKE) -f CMakeFiles/prepareData.dir/build.make CMakeFiles/prepareData.dir/DataProcess.cpp.o.provides.build
.PHONY : CMakeFiles/prepareData.dir/DataProcess.cpp.o.provides

CMakeFiles/prepareData.dir/DataProcess.cpp.o.provides.build: CMakeFiles/prepareData.dir/DataProcess.cpp.o


CMakeFiles/prepareData.dir/ORBMatching.cpp.o: CMakeFiles/prepareData.dir/flags.make
CMakeFiles/prepareData.dir/ORBMatching.cpp.o: ../ORBMatching.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/SatelliteSLAM/tools/c/prepareData/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/prepareData.dir/ORBMatching.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/prepareData.dir/ORBMatching.cpp.o -c /root/SatelliteSLAM/tools/c/prepareData/ORBMatching.cpp

CMakeFiles/prepareData.dir/ORBMatching.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/prepareData.dir/ORBMatching.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/SatelliteSLAM/tools/c/prepareData/ORBMatching.cpp > CMakeFiles/prepareData.dir/ORBMatching.cpp.i

CMakeFiles/prepareData.dir/ORBMatching.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/prepareData.dir/ORBMatching.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/SatelliteSLAM/tools/c/prepareData/ORBMatching.cpp -o CMakeFiles/prepareData.dir/ORBMatching.cpp.s

CMakeFiles/prepareData.dir/ORBMatching.cpp.o.requires:

.PHONY : CMakeFiles/prepareData.dir/ORBMatching.cpp.o.requires

CMakeFiles/prepareData.dir/ORBMatching.cpp.o.provides: CMakeFiles/prepareData.dir/ORBMatching.cpp.o.requires
	$(MAKE) -f CMakeFiles/prepareData.dir/build.make CMakeFiles/prepareData.dir/ORBMatching.cpp.o.provides.build
.PHONY : CMakeFiles/prepareData.dir/ORBMatching.cpp.o.provides

CMakeFiles/prepareData.dir/ORBMatching.cpp.o.provides.build: CMakeFiles/prepareData.dir/ORBMatching.cpp.o


# Object files for target prepareData
prepareData_OBJECTS = \
"CMakeFiles/prepareData.dir/main.cpp.o" \
"CMakeFiles/prepareData.dir/tinyxml2.cpp.o" \
"CMakeFiles/prepareData.dir/BasicFunc.cpp.o" \
"CMakeFiles/prepareData.dir/DataProcess.cpp.o" \
"CMakeFiles/prepareData.dir/ORBMatching.cpp.o"

# External object files for target prepareData
prepareData_EXTERNAL_OBJECTS =

prepareData: CMakeFiles/prepareData.dir/main.cpp.o
prepareData: CMakeFiles/prepareData.dir/tinyxml2.cpp.o
prepareData: CMakeFiles/prepareData.dir/BasicFunc.cpp.o
prepareData: CMakeFiles/prepareData.dir/DataProcess.cpp.o
prepareData: CMakeFiles/prepareData.dir/ORBMatching.cpp.o
prepareData: CMakeFiles/prepareData.dir/build.make
prepareData: /usr/local/lib/libopencv_shape.so.3.2.0
prepareData: /usr/local/lib/libopencv_stitching.so.3.2.0
prepareData: /usr/local/lib/libopencv_superres.so.3.2.0
prepareData: /usr/local/lib/libopencv_videostab.so.3.2.0
prepareData: /usr/local/lib/libopencv_viz.so.3.2.0
prepareData: /usr/local/lib/libDBoW3.a
prepareData: /usr/local/lib/libopencv_objdetect.so.3.2.0
prepareData: /usr/local/lib/libopencv_calib3d.so.3.2.0
prepareData: /usr/local/lib/libopencv_features2d.so.3.2.0
prepareData: /usr/local/lib/libopencv_flann.so.3.2.0
prepareData: /usr/local/lib/libopencv_highgui.so.3.2.0
prepareData: /usr/local/lib/libopencv_ml.so.3.2.0
prepareData: /usr/local/lib/libopencv_photo.so.3.2.0
prepareData: /usr/local/lib/libopencv_video.so.3.2.0
prepareData: /usr/local/lib/libopencv_videoio.so.3.2.0
prepareData: /usr/local/lib/libopencv_imgcodecs.so.3.2.0
prepareData: /usr/local/lib/libopencv_imgproc.so.3.2.0
prepareData: /usr/local/lib/libopencv_core.so.3.2.0
prepareData: CMakeFiles/prepareData.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/SatelliteSLAM/tools/c/prepareData/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable prepareData"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prepareData.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/prepareData.dir/build: prepareData

.PHONY : CMakeFiles/prepareData.dir/build

CMakeFiles/prepareData.dir/requires: CMakeFiles/prepareData.dir/main.cpp.o.requires
CMakeFiles/prepareData.dir/requires: CMakeFiles/prepareData.dir/tinyxml2.cpp.o.requires
CMakeFiles/prepareData.dir/requires: CMakeFiles/prepareData.dir/BasicFunc.cpp.o.requires
CMakeFiles/prepareData.dir/requires: CMakeFiles/prepareData.dir/DataProcess.cpp.o.requires
CMakeFiles/prepareData.dir/requires: CMakeFiles/prepareData.dir/ORBMatching.cpp.o.requires

.PHONY : CMakeFiles/prepareData.dir/requires

CMakeFiles/prepareData.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/prepareData.dir/cmake_clean.cmake
.PHONY : CMakeFiles/prepareData.dir/clean

CMakeFiles/prepareData.dir/depend:
	cd /root/SatelliteSLAM/tools/c/prepareData/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/SatelliteSLAM/tools/c/prepareData /root/SatelliteSLAM/tools/c/prepareData /root/SatelliteSLAM/tools/c/prepareData/cmake-build-debug /root/SatelliteSLAM/tools/c/prepareData/cmake-build-debug /root/SatelliteSLAM/tools/c/prepareData/cmake-build-debug/CMakeFiles/prepareData.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/prepareData.dir/depend

