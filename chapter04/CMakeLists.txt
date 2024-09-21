project(chapter04)

set(my_exe ${PROJECT_NAME}_exe)

set(my_sources
    cache_trashing.cpp
    read_file_into_string.cpp
    sum_scores.cpp
    priority_queues.cpp
    unordered_sets.cpp
    parallel_arrays.cpp
    main.cpp)

set(my_include ./)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} GTest::gtest)
