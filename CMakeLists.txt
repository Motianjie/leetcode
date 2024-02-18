cmake_minimum_required(VERSION 3.0)

project(TESTHELLOWORLD)
add_compile_definitions(LINUX=2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fno-elide-constructors -g -pthread -Wall")
add_executable(hello_world_cmake main.cpp)

