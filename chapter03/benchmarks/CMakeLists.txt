project(chapter03_benchmark)
set(my_exe ${PROJECT_NAME}_exe)

set(my_sources complexity.cpp)

set(my_include ./)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} PUBLIC benchmark::benchmark)
