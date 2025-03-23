cmake_minimum_required(VERSION 3.10)
project(mini_jvm)

message(STATUS "操作系统: ${CMAKE_SYSTEM_NAME}")
message(STATUS "CMake版本: ${CMAKE_VERSION}")
message(STATUS "C++编译器: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加编译选项
add_compile_options(-Wall -Wextra)

# 条件编译选项
if(UNIX AND NOT APPLE)
    message(STATUS "配置Linux特定设置...")
    # Linux特定设置
    add_compile_options(-fPIC)
    # 链接pthread库
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    
    # 检查C++17特性是否可用
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++17" COMPILER_SUPPORTS_CXX17)
    if(NOT COMPILER_SUPPORTS_CXX17)
        message(FATAL_ERROR "当前编译器不支持C++17。请安装支持C++17的GCC 7+或Clang 5+。")
    endif()
elseif(APPLE)
    message(STATUS "配置macOS特定设置...")
endif()

# 添加源文件目录
add_subdirectory(src)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}) 