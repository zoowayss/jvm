#include "classloader/class_loader.h"
#include "runtime/runtime_data.h"
#include "execution/interpreter.h"
#include "native/native_interface.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <signal.h>

using namespace mini_jvm;

// 信号处理函数
void signalHandler(int signal) {
    std::cerr << "捕获到信号: " << signal << std::endl;
    std::cerr << "程序异常终止" << std::endl;
    exit(signal);
}

// 示例：注册一个本地方法
JavaValue printHelloWorld(const std::vector<JavaValue>& args) {
    std::cout << "Hello from native method!" << std::endl;
    JavaValue result;
    result.i = 0;
    return result;
}

// 为主要的Java方法添加特殊本地实现
JavaValue handleSystemOutPrintln(const std::vector<JavaValue>& args) {
    // 在实际实现中，args应该包含要打印的字符串引用
    std::cout << "System.out.println: 本地实现" << std::endl;
    JavaValue result;
    result.i = 0;
    return result;
}

int main(int argc, char** argv) {
    // 设置信号处理函数，用于处理程序崩溃
    signal(SIGSEGV, signalHandler);
    signal(SIGILL, signalHandler);
    signal(SIGFPE, signalHandler);
    signal(SIGABRT, signalHandler);
    
    try {
        std::cout << "精简版JVM启动中..." << std::endl;
        
        // 初始化解释器
        Interpreter interpreter;
        
        // 注册本地方法
        NativeInterface::getInstance().registerNativeMethod(
            "java/lang/System",
            "println",
            "(Ljava/lang/String;)V",
            printHelloWorld
        );
        
        // 注册System.out.println方法
        NativeInterface::getInstance().registerNativeMethod(
            "java/io/PrintStream",
            "println",
            "(Ljava/lang/String;)V",
            handleSystemOutPrintln
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
    } catch (...) {
        std::cerr << "Unknown error occurred" << std::endl;
        return 2;
    }
    
    std::cout << "JVM执行完毕" << std::endl;
    return 0;
} 