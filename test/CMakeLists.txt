cmake_minimum_required(VERSION 3.0.2)
project(test_lib_link)

add_definitions(-std=c++11)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(hipnuc_imu)

add_executable(main main.cpp)
target_link_libraries(main hipnuc_imu)