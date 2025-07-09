cmake_minimum_required(VERSION 3.15)

project(firstProject CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(firstProject cpp/main.cpp)

find_package(Crow REQUIRED)
target_link_libraries(firstProject PUBLIC Crow::Crow)
