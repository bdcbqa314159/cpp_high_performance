project(chapter14)

set(my_exe ${PROJECT_NAME}_exe)

set(my_sources
    transform_tests.cpp
    reduce_foreach.cpp
    parallel_policy.cpp
    index_based_loop.cpp
    count_if.cpp
    copy_if_tests.cpp
    main.cpp)

set(my_include ./)
# link_directories(/usr/local/opt/llvm/lib/ /usr/local/opt/llvm/lib/c++/)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} GTest::gtest)

add_subdirectory(benchmarks)
