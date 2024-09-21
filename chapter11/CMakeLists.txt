project(chapter11)

set(my_exe ${PROJECT_NAME}_exe)

set(my_sources
    tasks.cpp
    stop_token.cpp
    semaphores.cpp
    print_thread_id.cpp
    lock_free_queue.cpp
    latches.cpp
    joinable_thread.cpp
    future_and_promises.cpp
    counter_mutex.cpp
    counter_data_race.cpp
    counter_atomic.cpp
    condition_variables.cpp
    barriers.cpp
    avoid_deadlock.cpp
    atomics.cpp
    async.cpp
    main.cpp)

set(my_include ./)

link_directories(/usr/local/opt/llvm/lib/ /usr/local/opt/llvm/lib/c++/)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} GTest::gtest unwind)
