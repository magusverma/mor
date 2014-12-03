# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.0

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
CMAKE_COMMAND = /opt/local/bin/cmake

# The command to remove a file.
RM = /opt/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/prasant/Documents/workspace/ImageAnalysis/moving_object_removal/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/prasant/Documents/workspace/ImageAnalysis/moving_object_removal/src

# Include any dependencies generated for this target.
include CMakeFiles/image_alignment.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/image_alignment.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/image_alignment.dir/flags.make

CMakeFiles/image_alignment.dir/image_alignment.cpp.o: CMakeFiles/image_alignment.dir/flags.make
CMakeFiles/image_alignment.dir/image_alignment.cpp.o: image_alignment.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /Users/prasant/Documents/workspace/ImageAnalysis/moving_object_removal/src/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/image_alignment.dir/image_alignment.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/image_alignment.dir/image_alignment.cpp.o -c /Users/prasant/Documents/workspace/ImageAnalysis/moving_object_removal/src/image_alignment.cpp

CMakeFiles/image_alignment.dir/image_alignment.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/image_alignment.dir/image_alignment.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/prasant/Documents/workspace/ImageAnalysis/moving_object_removal/src/image_alignment.cpp > CMakeFiles/image_alignment.dir/image_alignment.cpp.i

CMakeFiles/image_alignment.dir/image_alignment.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/image_alignment.dir/image_alignment.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/prasant/Documents/workspace/ImageAnalysis/moving_object_removal/src/image_alignment.cpp -o CMakeFiles/image_alignment.dir/image_alignment.cpp.s

CMakeFiles/image_alignment.dir/image_alignment.cpp.o.requires:
.PHONY : CMakeFiles/image_alignment.dir/image_alignment.cpp.o.requires

CMakeFiles/image_alignment.dir/image_alignment.cpp.o.provides: CMakeFiles/image_alignment.dir/image_alignment.cpp.o.requires
	$(MAKE) -f CMakeFiles/image_alignment.dir/build.make CMakeFiles/image_alignment.dir/image_alignment.cpp.o.provides.build
.PHONY : CMakeFiles/image_alignment.dir/image_alignment.cpp.o.provides

CMakeFiles/image_alignment.dir/image_alignment.cpp.o.provides.build: CMakeFiles/image_alignment.dir/image_alignment.cpp.o

# Object files for target image_alignment
image_alignment_OBJECTS = \
"CMakeFiles/image_alignment.dir/image_alignment.cpp.o"

# External object files for target image_alignment
image_alignment_EXTERNAL_OBJECTS =

image_alignment: CMakeFiles/image_alignment.dir/image_alignment.cpp.o
image_alignment: CMakeFiles/image_alignment.dir/build.make
image_alignment: /usr/local/lib/libopencv_videostab.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_videoio.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_video.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_ts.a
image_alignment: /usr/local/lib/libopencv_superres.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_stitching.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_shape.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_photo.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_objdetect.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_ml.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_imgproc.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_imgcodecs.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_highgui.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_flann.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_features2d.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_core.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_calib3d.3.0.0.dylib
image_alignment: /usr/local/share/OpenCV/3rdparty/lib/libippicv.a
image_alignment: /usr/local/lib/libopencv_features2d.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_ml.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_highgui.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_videoio.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_imgcodecs.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_flann.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_video.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_imgproc.3.0.0.dylib
image_alignment: /usr/local/lib/libopencv_core.3.0.0.dylib
image_alignment: CMakeFiles/image_alignment.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable image_alignment"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/image_alignment.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/image_alignment.dir/build: image_alignment
.PHONY : CMakeFiles/image_alignment.dir/build

CMakeFiles/image_alignment.dir/requires: CMakeFiles/image_alignment.dir/image_alignment.cpp.o.requires
.PHONY : CMakeFiles/image_alignment.dir/requires

CMakeFiles/image_alignment.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/image_alignment.dir/cmake_clean.cmake
.PHONY : CMakeFiles/image_alignment.dir/clean

CMakeFiles/image_alignment.dir/depend:
	cd /Users/prasant/Documents/workspace/ImageAnalysis/moving_object_removal/src && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/prasant/Documents/workspace/ImageAnalysis/moving_object_removal/src /Users/prasant/Documents/workspace/ImageAnalysis/moving_object_removal/src /Users/prasant/Documents/workspace/ImageAnalysis/moving_object_removal/src /Users/prasant/Documents/workspace/ImageAnalysis/moving_object_removal/src /Users/prasant/Documents/workspace/ImageAnalysis/moving_object_removal/src/CMakeFiles/image_alignment.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/image_alignment.dir/depend

