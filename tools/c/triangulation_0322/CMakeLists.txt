cmake_minimum_required(VERSION 2.6)
project(triangulation_0322)

set( CMAKE_CXX_FLAGS "-std=c++11 -O3" )

find_package( OpenCV 3.1 REQUIRED )

include_directories( 
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(triangulation_0322 common.cpp MatrixCalculation.cpp ORBMatching.cpp main.cpp)

target_link_libraries( triangulation_0322 ${OpenCV_LIBS} )

install(TARGETS triangulation_0322 RUNTIME DESTINATION bin)
