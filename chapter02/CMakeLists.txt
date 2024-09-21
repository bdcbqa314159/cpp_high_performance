project(chapter02)

set(my_exe ${PROJECT_NAME}_exe)

set(my_sources
    auto.cpp
    propagate_const.cpp
    exception_safety.cpp
    move_semantics.cpp
    lambda.cpp
    lambda_capture.cpp
    lambda_generic.cpp
    lambda_std_function.cpp
    lambda_types.cpp
    main.cpp)

set(my_include ./)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} GTest::gtest Boost::system Boost::regex
                      Boost::thread)

add_subdirectory(benchmarks)
