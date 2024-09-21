project(chapter09)

set(my_exe ${PROJECT_NAME}_exe)

set(my_sources
    variant.cpp
    variadic_template_parameter_pack.cpp
    tuple_algorithms.cpp
    tuple_accessing_elements.cpp
    example_projections.cpp
    example_reflection_concepts.cpp
    heterogenous_container_of_variants.cpp
    pair.cpp
    tuple.cpp
    optional.cpp
    any.cpp
    example_reflection.cpp
    main.cpp)

set(my_include ./)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} GTest::gtest)
