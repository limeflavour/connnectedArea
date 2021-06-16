cmake_minimum_required(VERSION 3.19)
project(connnectedArea)

set(CMAKE_CXX_STANDARD 14)

set(OpenCV_DIR "D:\\opencv330\\opencv\\clion64withCon\\install")
# find required opencv
find_package(OpenCV REQUIRED)
# directory of opencv headers
include_directories(${OpenCV_INCLUDE_DIRS})
# directory of opencv library
link_directories(${OpenCV_LIBRARY_DIRS})
# name of executable file and path of source file
add_executable(connnectedArea main.cpp)
# opencv libraries
target_link_libraries(connnectedArea ${OpenCV_LIBS})

