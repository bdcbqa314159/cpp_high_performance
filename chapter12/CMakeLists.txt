project(chapter12)

set(my_exe ${PROJECT_NAME}_exe)

set(my_sources
    lin_space_callback.cpp
    lin_space_coroutine.cpp
    lin_space_eager.cpp
    lin_space_iterator.cpp
    lin_space_ranges.cpp
    passing_coroutines_around.cpp
    index_compression_example.cpp
    generator_example.cpp
    dangling_references.cpp
    resumable_minimal_example.cpp
    initial_example.cpp
    main.cpp)

set(my_include ./)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} GTest::gtest)
