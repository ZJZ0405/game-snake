cmake_minimum_required(VERSION 2.6)
# 创建工程
project(game-snake)
#C++版本为 11
set(CMAKE_CXX_FLAGS "-std=c++11")
#找OpenCV 4.6.0 安装路径
find_package(OpenCV 4.6.0 REQUIRED)
#加载 OpenCV 4.6.0 的头文件
include_directories(${OpenCV_INCLUDE_DIRS})
#将程序生成为可执行文件
add_executable(GUI-main src/GUI-main.cpp src/GSnake.cpp src/Game.cpp)
#链接 lib 文件到可执行文件中
target_link_libraries(main ${OpenCV_LIBS})
