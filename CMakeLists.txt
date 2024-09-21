cmake_minimum_required(VERSION 3.30)

project(
  cpp_high_performance
  VERSION 1.0.0
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")

find_package(Boost REQUIRED COMPONENTS system thread regex)
find_package(benchmark CONFIG REQUIRED)
find_package(gtest CONFIG REQUIRED)

if(Boost_FOUND)
  message(STATUS "boost_includes: ${Boost_INCLUDE_DIRS}")
endif()

add_subdirectory(chapter01)
add_subdirectory(chapter02)
add_subdirectory(chapter03)
add_subdirectory(chapter04)
add_subdirectory(chapter05)
add_subdirectory(chapter06)
add_subdirectory(chapter07)
add_subdirectory(chapter08)
add_subdirectory(chapter09)
add_subdirectory(chapter10)
add_subdirectory(chapter11)
add_subdirectory(chapter12)
add_subdirectory(chapter13)
add_subdirectory(chapter14)
