cmake_minimum_required(VERSION 2.8)
project( Assignment_1 )
find_package( OpenCV REQUIRED )

add_executable( median median.cpp )
target_link_libraries( median ${OpenCV_LIBS} )

add_executable( affine affine.cpp )
target_link_libraries( affine ${OpenCV_LIBS} )

add_executable( feature_matching feature_matching.cpp )
target_link_libraries( feature_matching ${OpenCV_LIBS} )

add_executable( get_mask get_mask.cpp )
target_link_libraries( get_mask ${OpenCV_LIBS} )
