#!/bin/bash

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

echo -e "${YELLOW}清理构建环境...${NC}"

# 删除构建目录
if [ -d "build" ]; then
    echo -e "${GREEN}删除构建目录...${NC}"
    rm -rf build
    echo -e "${GREEN}构建目录已清除${NC}"
else
    echo -e "${YELLOW}构建目录不存在，无需清理${NC}"
fi

# 删除可能存在的CMake缓存
find . -name "CMakeCache.txt" -delete
find . -name "CMakeFiles" -type d -exec rm -rf {} +
find . -name "cmake_install.cmake" -delete

# 删除编译生成的类文件
find . -name "*.class" -delete

echo -e "${GREEN}清理完成!${NC}" 