#!/bin/bash

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}开始构建精简版JVM...${NC}"

# 检查必要的工具
echo -e "${YELLOW}检查系统环境...${NC}"

# 检查CMake
if ! command -v cmake &> /dev/null; then
    echo -e "${RED}错误: cmake未安装${NC}"
    echo -e "请使用以下命令安装cmake:"
    echo -e "${YELLOW}sudo apt-get install cmake${NC} (Debian/Ubuntu)"
    echo -e "${YELLOW}sudo yum install cmake${NC} (CentOS/RHEL)"
    exit 1
fi

# 检查编译器
if ! command -v g++ &> /dev/null; then
    echo -e "${RED}错误: g++未安装${NC}"
    echo -e "请使用以下命令安装g++:"
    echo -e "${YELLOW}sudo apt-get install g++${NC} (Debian/Ubuntu)"
    echo -e "${YELLOW}sudo yum install gcc-c++${NC} (CentOS/RHEL)"
    exit 1
fi

# 检查Java
if ! command -v javac &> /dev/null; then
    echo -e "${YELLOW}警告: javac未安装, 可能无法编译测试类${NC}"
fi

# 清理并创建构建目录
echo -e "${GREEN}清理并创建构建目录...${NC}"
rm -rf build
mkdir -p build
cd build

# 运行CMake
echo -e "${GREEN}配置项目...${NC}"
cmake .. || { echo -e "${RED}CMake配置失败${NC}"; exit 1; }

# 编译项目
echo -e "${GREEN}编译项目...${NC}"
make -j$(nproc 2>/dev/null || echo 2) || { echo -e "${RED}编译失败${NC}"; exit 1; }

# 返回到项目根目录
cd ..

# 编译测试类
echo -e "${GREEN}编译测试类...${NC}"
if command -v javac &> /dev/null; then
    javac TestClass.java
    cp TestClass.class build/
    echo -e "${GREEN}测试类编译并复制完成${NC}"
else
    echo -e "${YELLOW}跳过测试类编译${NC}"
fi

echo -e "${GREEN}构建完成!${NC}"
echo -e "可以使用以下命令运行JVM:"
echo -e "${YELLOW}cd build && ./src/mini_jvm${NC}"

# 提示运行
echo -e "${GREEN}是否立即运行JVM? [y/N]${NC}"
read -r choice
if [[ "$choice" =~ ^[Yy]$ ]]; then
    cd build
    ./src/mini_jvm
fi 