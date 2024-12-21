# 1
* src/example.cpp 是单独使用imu的C++示例
# 2
- test/main.cpp 是把hipnuc_imu作为库调用
- 使用时只需
```shell
add_subdirectory(hipnuc_imu)
target_link_libraries(<exe> hipnuc_imu)
```
