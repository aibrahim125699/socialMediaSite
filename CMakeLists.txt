cmake_minimum_required(VERSION 3.15)

project(firstProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(firstProject main.cpp)

target_include_directories(firstProject PRIVATE ${CMAKE_SOURCE_DIR}/include)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)