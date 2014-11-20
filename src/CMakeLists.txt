cmake_minimum_required(VERSION 2.8)
project( Assignment_1 )
find_package( OpenCV REQUIRED )

add_executable( median median.cpp )
target_link_libraries( median ${OpenCV_LIBS} )
