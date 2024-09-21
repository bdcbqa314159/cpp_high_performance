project(chapter10)

set(my_exe ${PROJECT_NAME}_exe)

set(my_sources pipe_operator.cpp string_concat_proxy_tests.cpp
               vec2d_length_proxy_tests.cpp main.cpp)

set(my_include ./)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} GTest::gtest)

add_subdirectory(benchmarks)
