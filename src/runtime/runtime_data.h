#ifndef MINI_JVM_RUNTIME_DATA_H
#define MINI_JVM_RUNTIME_DATA_H

#include <vector>
#include <memory>
#include <cstdint>

namespace mini_jvm {

// 简化的Java值类型
union JavaValue {
    int32_t i;
    int64_t l;
    float f;
    double d;
    void* ref;
};

// 操作数栈
class OperandStack {
public:
    void push(JavaValue value);
    JavaValue pop();
    bool isEmpty() const;
    void reserve(size_t size);
private:
    std::vector<JavaValue> stack;
};

// 局部变量表
class LocalVars {
public:
    explicit LocalVars(size_t maxLocals);
    void setVar(size_t index, JavaValue value);
    JavaValue getVar(size_t index) const;
private:
    std::vector<JavaValue> vars;
};

// 栈帧
class Frame {
public:
    Frame(size_t maxLocals, size_t maxStack);
    LocalVars& getLocalVars();
    OperandStack& getOperandStack();
private:
    LocalVars localVars;
    OperandStack operandStack;
};

// 简化的堆内存管理
class Heap {
public:
    static Heap& getInstance();
    void* allocate(size_t size);
    void deallocate(void* ptr);
private:
    Heap() = default;
    // 使用简单的内存池实现
    std::vector<uint8_t> memoryPool;
};

} // namespace mini_jvm

#endif // MINI_JVM_RUNTIME_DATA_H 