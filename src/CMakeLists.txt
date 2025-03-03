cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(cpp-shenanigans LANGUAGES CXX)

add_subdirectory(cli)
add_subdirectory(hashmap)
