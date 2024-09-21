project(chapter08)

set(my_exe ${PROJECT_NAME}_exe)

set(my_sources
    constraints_and_concepts.cpp
    constexpr_if_mod.cpp
    constexpr_if_animals.cpp
    compile_time_hash.cpp
    integer_as_template_parameter.cpp
    abbreviated_function_templates.cpp
    point2d_concepts.cpp
    point2d_unconstrained.cpp
    runtime_polymorphism_animals.cpp
    safe_cast.cpp
    static_assert.cpp
    template_class.cpp
    template_function.cpp
    type_traits.cpp
    main.cpp)

set(my_include ./)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} GTest::gtest)

# add_subdirectory(benchmarks)
