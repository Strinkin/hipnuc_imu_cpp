cmake_minimum_required(VERSION 3.0.2)
project(hipnuc_imu)

file(GLOB_RECURSE HIPNUC_DEC_SRCS ${PROJECT_SOURCE_DIR}/include/*.c)


# hipnuc_imu data parser
add_library(hipnuc_dec SHARED ${HIPNUC_DEC_SRCS})
target_include_directories(hipnuc_dec PUBLIC ${PROJECT_SOURCE_DIR}/include)

# example
add_executable(example ${PROJECT_SOURCE_DIR}/src/example.cpp)
target_link_libraries(example PRIVATE hipnuc_dec)

# 
add_library(hipnuc_imu SHARED ${PROJECT_SOURCE_DIR}/src/hipnuc_imu.hpp ${HIPNUC_DEC_SRCS})
target_include_directories(hipnuc_imu PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(hipnuc_imu PUBLIC hipnuc_dec)

