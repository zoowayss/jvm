# 精简版JVM

这是一个用C++实现的精简版JVM，专门针对资源和内存环境受限的情况，对标准JVM进行了裁剪简化。

## 主要特点

- 轻量级设计，内存占用小
- 简化的类加载机制
- 基本的字节码解释执行
- 精简的运行时数据区
- 简单的本地方法接口
- 跨平台支持（Linux/macOS）

## 系统要求

- C++17兼容的编译器 (GCC 7+/Clang 5+)
- CMake 3.10+
- 可选: JDK (用于编译测试类)

## 项目结构

```
mini_jvm/
├── src/                       # 源代码目录
│   ├── classloader/           # 类加载子系统
│   ├── runtime/               # 运行时数据区
│   ├── execution/             # 执行引擎
│   └── native/                # 本地方法接口
├── CMakeLists.txt             # CMake配置文件
├── build_linux.sh             # Linux构建脚本
└── TestClass.java             # 测试类
```

## 构建说明

### Linux

可以使用提供的构建脚本：

```bash
./build_linux.sh
```

或手动构建：

```bash
mkdir -p build
cd build
cmake ..
make
```

### macOS

```bash
mkdir -p build
cd build
cmake ..
make
```

## 运行说明

编译完成后，可执行文件位于`build/src/mini_jvm`。运行前需确保当前目录中有`TestClass.class`文件：

```bash
cd build
./src/mini_jvm
```

## 限制与简化

1. 只支持基本的字节码指令
2. 没有实现JIT编译
3. 简化的内存管理，没有完整的垃圾回收
4. 不支持线程
5. 不支持复杂的类型转换
6. 没有实现完整的异常处理机制

## 后续改进方向

1. 添加更多字节码指令支持
2. 实现简单的垃圾回收
3. 增加基本的类型检查和验证
4. 扩展本地方法接口
5. 添加简单的异常处理 