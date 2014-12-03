cmake_minimum_required(VERSION 2.8)
project( Assignment_1 )
find_package( OpenCV REQUIRED )

add_executable( median median.cpp )
target_link_libraries( median ${OpenCV_LIBS} )

add_executable( registration registration.cpp )
target_link_libraries( registration ${OpenCV_LIBS} )

add_executable( image_alignment image_alignment.cpp )
target_link_libraries( image_alignment ${OpenCV_LIBS} )

add_executable( align_affine align_affine.cpp )
target_link_libraries( align_affine ${OpenCV_LIBS} )
