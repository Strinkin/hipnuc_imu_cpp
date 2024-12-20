# hipnuc_imu_cpp
- 该项目修改自hipnuc的官方示例: https://github.com/hipnuc/products.git
- 提供了C++的二次开发, 包括:
1. 直接运行的示例
2. 作为库被主项目调用的示例
# 说明
## 1
* src/example.cpp 是单独使用imu的C++示例
## 2
- test/main.cpp 是把hipnuc_imu作为库调用
- 使用时只需
```shell
add_subdirectory(hipnuc_imu)
target_link_libraries(<exe> hipnuc_imu)
```
