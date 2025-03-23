#include "runtime_data.h"
#include <stdexcept>

namespace mini_jvm {

// OperandStack implementation
void OperandStack::push(JavaValue value) {
    stack.push_back(value);
}

JavaValue OperandStack::pop() {
    if (stack.empty()) {
        throw std::runtime_error("Stack underflow");
    }
    JavaValue value = stack.back();
    stack.pop_back();
    return value;
}

bool OperandStack::isEmpty() const {
    return stack.empty();
}

void OperandStack::reserve(size_t size) {
    stack.reserve(size);
}

// LocalVars implementation
LocalVars::LocalVars(size_t maxLocals) : vars(maxLocals) {}

void LocalVars::setVar(size_t index, JavaValue value) {
    if (index >= vars.size()) {
        throw std::out_of_range("Local variable index out of range");
    }
    vars[index] = value;
}

JavaValue LocalVars::getVar(size_t index) const {
    if (index >= vars.size()) {
        throw std::out_of_range("Local variable index out of range");
    }
    return vars[index];
}

// Frame implementation
Frame::Frame(size_t maxLocals, size_t maxStack) 
    : localVars(maxLocals), operandStack() {
    // 预分配操作数栈空间
    operandStack.reserve(maxStack);
}

LocalVars& Frame::getLocalVars() {
    return localVars;
}

OperandStack& Frame::getOperandStack() {
    return operandStack;
}

// Heap implementation
Heap& Heap::getInstance() {
    static Heap instance;
    return instance;
}

void* Heap::allocate(size_t size) {
    // 简化的内存分配实现
    size_t currentSize = memoryPool.size();
    memoryPool.resize(currentSize + size);
    return &memoryPool[currentSize];
}

void Heap::deallocate(void* ptr) {
    // 简化的内存释放实现
    // 在实际实现中，这里需要更复杂的内存管理策略
    (void)ptr; // 避免未使用参数警告
}

} // namespace mini_jvm 