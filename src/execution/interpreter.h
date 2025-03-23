#ifndef MINI_JVM_INTERPRETER_H
#define MINI_JVM_INTERPRETER_H

#include "../runtime/runtime_data.h"
#include "../classloader/class_loader.h"
#include <vector>
#include <memory>

namespace mini_jvm {

// 字节码指令
enum class ByteCode : uint8_t {
    NOP = 0x00,
    ACONST_NULL = 0x01,
    ICONST_M1 = 0x02,
    ICONST_0 = 0x03,
    ICONST_1 = 0x04,
    ICONST_2 = 0x05,
    ICONST_3 = 0x06,
    ICONST_4 = 0x07,
    ICONST_5 = 0x08,
    ILOAD = 0x15,
    ILOAD_0 = 0x1A,
    ILOAD_1 = 0x1B,
    ILOAD_2 = 0x1C,
    ILOAD_3 = 0x1D,
    ISTORE = 0x36,
    ISTORE_0 = 0x3B,
    ISTORE_1 = 0x3C,
    ISTORE_2 = 0x3D,
    ISTORE_3 = 0x3E,
    IADD = 0x60,
    ISUB = 0x64,
    IMUL = 0x68,
    IDIV = 0x6c,
    IRETURN = 0xac,
    RETURN = 0xb1
    // 这里只实现了最基本的几个指令
};

class Interpreter {
public:
    Interpreter();
    
    // 执行方法
    JavaValue executeMethod(const std::string& className,
                          const std::string& methodName,
                          const std::string& descriptor,
                          const std::vector<JavaValue>& args);

private:
    // 执行单个指令
    void executeInstruction(Frame& frame, ByteCode opcode);
    
    // 执行字节码
    void executeByteCode(Frame& frame, const std::vector<uint8_t>& code);
    
    std::shared_ptr<ClassLoader> classLoader;
};

} // namespace mini_jvm

#endif // MINI_JVM_INTERPRETER_H 