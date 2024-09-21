project(chapter05_benchmark)
set(my_exe_1 ${PROJECT_NAME}_exe_1)
set(my_exe_2 ${PROJECT_NAME}_exe_2)

set(my_sources_1 sorting_bm.cpp)
set(my_sources_2 find_bm.cpp)

set(my_include ./)

add_executable(${my_exe_1} ${my_sources_1})
target_include_directories(${my_exe_1} PUBLIC ${my_include})
target_link_libraries(${my_exe_1} PUBLIC benchmark::benchmark)

add_executable(${my_exe_2} ${my_sources_2})
target_include_directories(${my_exe_2} PUBLIC ${my_include})
target_link_libraries(${my_exe_2} PUBLIC benchmark::benchmark)
