cmake_minimum_required(VERSION 3.10)
project(prepareData)

set(CMAKE_CXX_STANDARD 11)

# OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_DIRS})

# dbow3
# dbow3 is a simple lib so I assume you installed it in default directory
set( DBoW3_INCLUDE_DIRS "/usr/local/include" )
set( DBoW3_LIBS "/usr/local/lib/libDBoW3.a" )

add_executable(prepareData main.cpp tinyxml2.cpp tinyxml2.h BasicFunc.cpp BasicFunc.h DataProcess.cpp DataProcess.h ORBMatching.cpp ORBMatching.h)

# 与G2O和OpenCV链接
target_link_libraries(prepareData
        ${OpenCV_LIBS}
        ${DBoW3_LIBS}
        )