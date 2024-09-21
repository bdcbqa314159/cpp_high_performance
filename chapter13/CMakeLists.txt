project(chapter13)

set(my_exe ${PROJECT_NAME}_exe)
set(server_exe ${PROJECT_NAME}_server_exe)

set(my_sources task_ex.cpp asio_timer_callback.cpp asio_timer_coro.cpp main.cpp)
set(server_sources asio_server.cpp)

set(my_include ./)

include_directories(${Boost_INCLUDE_DIRS})

link_directories(/usr/local/opt/llvm/lib/ /usr/local/opt/llvm/lib/c++/)

add_executable(${my_exe} ${my_sources})
target_include_directories(${my_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} GTest::gtest Boost::thread Boost::system
                      Boost::regex unwind)

add_executable(${server_exe} ${server_sources})
target_include_directories(${server_exe} PUBLIC ${my_include})
target_link_libraries(${my_exe} Boost::thread Boost::system Boost::regex unwind)
