project(chapter02_benchmark)

set(my_exe ${PROJECT_NAME}_exe)

set(my_sources lambda_vs_stdfunction_benchmark.cpp)

set(my_include ./)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} PUBLIC benchmark::benchmark)
