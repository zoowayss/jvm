#include "classloader/class_loader.h"
#include "runtime/runtime_data.h"
#include "execution/interpreter.h"
#include "native/native_interface.h"
#include <iostream>

using namespace mini_jvm;

// 示例：注册一个本地方法
JavaValue printHelloWorld(const std::vector<JavaValue>& args) {
    std::cout << "Hello from native method!" << std::endl;
    JavaValue result;
    result.i = 0;
    return result;
}

int main() {
    try {
        // 初始化解释器
        Interpreter interpreter;
        
        // 注册本地方法
        NativeInterface::getInstance().registerNativeMethod(
            "java/lang/System",
            "println",
            "(Ljava/lang/String;)V",
            printHelloWorld
        );
        
        // 直接调用本地方法
        std::cout << "直接调用本地方法:" << std::endl;
        std::vector<JavaValue> nativeArgs;
        NativeInterface::getInstance().callNativeMethod(
            "java/lang/System",
            "println",
            "(Ljava/lang/String;)V",
            nativeArgs
        );
        
        // 创建测试参数
        std::vector<JavaValue> args;
        JavaValue arg;
        arg.i = 42;
        args.push_back(arg);
        
        // 执行Java方法
        JavaValue result = interpreter.executeMethod(
            "TestClass",
            "testMethod",
            "(I)I",
            args
        );
        
        std::cout << "Method execution result: " << result.i << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 