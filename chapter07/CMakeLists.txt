project(chapter07)

set(my_exe ${PROJECT_NAME}_exe)

set(my_sources
    polymorphic_memory_allocators.cpp
    operator_new.cpp
    padding.cpp
    raii_connection.cpp
    alignement.cpp
    user_arena.cpp
    placement_new.cpp
    short_alloc.cpp
    small_size_optimization.cpp
    stack_memory.cpp
    stack_size.cpp
    main.cpp)

set(my_include ./)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} GTest::gtest)
