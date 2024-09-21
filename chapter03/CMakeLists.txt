project(chapter03)

set(my_exe ${PROJECT_NAME}_exe)

set(my_sources scoped_timer.cpp linear_search_point.cpp linear_search.cpp
               binary_search.cpp insertion_sort.cpp main.cpp)

set(my_include ./)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} GTest::gtest)

add_subdirectory(benchmarks)
