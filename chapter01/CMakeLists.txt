project(chapter01)

set(my_exe ${PROJECT_NAME}_exe)

set(my_sources abstractions.cpp heap_allocations.cpp const_correctness.cpp
               references.cpp value_semantics.cpp main.cpp)

set(my_include ./)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} GTest::gtest)
