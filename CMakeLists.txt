cmake_minimum_required(VERSION 3.10)
project(mini_jvm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加编译选项
add_compile_options(-Wall -Wextra)

# 添加源文件目录
add_subdirectory(src)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}) 