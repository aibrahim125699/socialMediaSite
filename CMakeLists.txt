cmake_minimum_required(VERSION 3.15)

project(firstProject CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(Sodium
    GIT_REPOSITORY https://github.com/robinlinden/libsodium-cmake.git
    GIT_TAG e5b985ad0dd235d8c4307ea3a385b45e76c74c6a
)
set(SODIUM_DISABLE_TESTS ON)
FetchContent_MakeAvailable(Sodium)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(firstProject cpp/main.cpp)

find_package(Crow REQUIRED)
target_link_libraries(firstProject PUBLIC Crow::Crow)
target_link_libraries(firstProject PRIVATE sodium)
