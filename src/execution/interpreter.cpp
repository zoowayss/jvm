#include "interpreter.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace mini_jvm {

Interpreter::Interpreter() : classLoader(std::make_shared<ClassLoader>()) {}

JavaValue Interpreter::executeMethod(const std::string& className,
                                   const std::string& methodName,
                                   const std::string& descriptor,
                                   const std::vector<JavaValue>& args) {
    // 加载类
    auto classFile = classLoader->loadClass(className);
    
    std::cout << "执行方法: " << className << "." << methodName << descriptor << std::endl;
    
    // 模拟从类文件中获取字节码
    // 在实际实现中，应该从classFile中找到对应的方法
    std::vector<uint8_t> code;
    
    // 根据类名和方法名，生成一些字节码进行执行
    // 这里我们模拟一个简单方法，将输入参数加1并返回
    code.push_back(static_cast<uint8_t>(ByteCode::ILOAD_0));  // 加载第一个参数
    code.push_back(static_cast<uint8_t>(ByteCode::ICONST_1)); // 加载常量1
    code.push_back(static_cast<uint8_t>(ByteCode::IADD));     // 执行加法
    code.push_back(static_cast<uint8_t>(ByteCode::IRETURN));  // 返回结果
    
    // 创建栈帧
    Frame frame(args.size() + 4, 10); // 简化的栈帧大小
    
    // 加载参数到局部变量表
    for (size_t i = 0; i < args.size(); i++) {
        frame.getLocalVars().setVar(i, args[i]);
        std::cout << "参数 " << i << " = " << args[i].i << std::endl;
    }
    
    // 执行字节码
    executeByteCode(frame, code);
    
    // 如果方法有返回值，它会在操作数栈顶
    if (!frame.getOperandStack().isEmpty()) {
        JavaValue result = frame.getOperandStack().pop();
        std::cout << "方法返回值: " << result.i << std::endl;
        return result;
    }
    
    // 无返回值的方法
    JavaValue result;
    result.i = 0;
    return result;
}

void Interpreter::executeInstruction(Frame& frame, ByteCode opcode) {
    OperandStack& stack = frame.getOperandStack();
    LocalVars& locals = frame.getLocalVars();
    
    switch (opcode) {
        case ByteCode::NOP:
            std::cout << "执行: NOP" << std::endl;
            break;
            
        case ByteCode::ACONST_NULL: {
            std::cout << "执行: ACONST_NULL" << std::endl;
            JavaValue value;
            value.ref = nullptr;
            stack.push(value);
            break;
        }
            
        case ByteCode::ICONST_M1: {
            std::cout << "执行: ICONST_M1" << std::endl;
            JavaValue value;
            value.i = -1;
            stack.push(value);
            break;
        }
            
        case ByteCode::ICONST_0: {
            std::cout << "执行: ICONST_0" << std::endl;
            JavaValue value;
            value.i = 0;
            stack.push(value);
            break;
        }

        case ByteCode::ICONST_1: {
            std::cout << "执行: ICONST_1" << std::endl;
            JavaValue value;
            value.i = 1;
            stack.push(value);
            break;
        }
            
        case ByteCode::ILOAD_0: {
            std::cout << "执行: ILOAD_0" << std::endl;
            JavaValue value = locals.getVar(0);
            stack.push(value);
            break;
        }
            
        case ByteCode::IADD: {
            std::cout << "执行: IADD" << std::endl;
            JavaValue v2 = stack.pop();
            JavaValue v1 = stack.pop();
            JavaValue result;
            result.i = v1.i + v2.i;
            std::cout << "  " << v1.i << " + " << v2.i << " = " << result.i << std::endl;
            stack.push(result);
            break;
        }
            
        case ByteCode::ISUB: {
            std::cout << "执行: ISUB" << std::endl;
            JavaValue v2 = stack.pop();
            JavaValue v1 = stack.pop();
            JavaValue result;
            result.i = v1.i - v2.i;
            std::cout << "  " << v1.i << " - " << v2.i << " = " << result.i << std::endl;
            stack.push(result);
            break;
        }
            
        case ByteCode::IMUL: {
            std::cout << "执行: IMUL" << std::endl;
            JavaValue v2 = stack.pop();
            JavaValue v1 = stack.pop();
            JavaValue result;
            result.i = v1.i * v2.i;
            std::cout << "  " << v1.i << " * " << v2.i << " = " << result.i << std::endl;
            stack.push(result);
            break;
        }
            
        case ByteCode::IDIV: {
            std::cout << "执行: IDIV" << std::endl;
            JavaValue v2 = stack.pop();
            JavaValue v1 = stack.pop();
            if (v2.i == 0) {
                throw std::runtime_error("Division by zero");
            }
            JavaValue result;
            result.i = v1.i / v2.i;
            std::cout << "  " << v1.i << " / " << v2.i << " = " << result.i << std::endl;
            stack.push(result);
            break;
        }
            
        case ByteCode::IRETURN:
            std::cout << "执行: IRETURN" << std::endl;
            // 返回值已经在栈顶
            break;
            
        case ByteCode::RETURN:
            std::cout << "执行: RETURN" << std::endl;
            // void方法返回
            break;
            
        default:
            throw std::runtime_error("不支持的字节码: " + 
                                   std::to_string(static_cast<int>(opcode)));
    }
}

void Interpreter::executeByteCode(Frame& frame, const std::vector<uint8_t>& code) {
    std::cout << "开始执行字节码，长度: " << code.size() << std::endl;
    
    for (size_t pc = 0; pc < code.size(); pc++) {
        ByteCode opcode = static_cast<ByteCode>(code[pc]);
        std::cout << "PC=" << pc << ", 操作码: 0x" << std::hex << static_cast<int>(opcode) << std::dec << std::endl;
        
        executeInstruction(frame, opcode);
        
        // 如果是返回指令，终止执行
        if (opcode == ByteCode::IRETURN || opcode == ByteCode::RETURN) {
            std::cout << "遇到返回指令，终止执行" << std::endl;
            break;
        }
    }
    
    std::cout << "字节码执行完毕" << std::endl;
}

} // namespace mini_jvm 