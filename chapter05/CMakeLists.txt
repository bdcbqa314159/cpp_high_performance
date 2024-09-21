project(chapter05)

set(my_exe ${PROJECT_NAME}_exe)

set(my_sources
    contains_duplicates.cpp
    everyday_problems.cpp
    generic_algorithms.cpp
    grid.cpp
    sorting.cpp
    standard_algorithm_features.cpp
    main.cpp)

set(my_include ./)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} GTest::gtest)

add_subdirectory(benchmarks)
