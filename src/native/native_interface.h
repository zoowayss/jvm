#ifndef MINI_JVM_NATIVE_INTERFACE_H
#define MINI_JVM_NATIVE_INTERFACE_H

#include "../runtime/runtime_data.h"
#include <string>
#include <functional>
#include <unordered_map>
#include <memory>

namespace mini_jvm {

// 本地方法函数类型
using NativeMethod = std::function<JavaValue(const std::vector<JavaValue>&)>;

class NativeInterface {
public:
    static NativeInterface& getInstance();
    
    // 注册本地方法
    void registerNativeMethod(const std::string& className,
                            const std::string& methodName,
                            const std::string& descriptor,
                            NativeMethod method);
    
    // 调用本地方法
    JavaValue callNativeMethod(const std::string& className,
                              const std::string& methodName,
                              const std::string& descriptor,
                              const std::vector<JavaValue>& args);
    
    // 检查方法是否存在
    bool hasNativeMethod(const std::string& className,
                        const std::string& methodName,
                        const std::string& descriptor);
    
private:
    NativeInterface() = default;
    
    // 禁用拷贝构造函数和赋值操作符
    NativeInterface(const NativeInterface&) = delete;
    NativeInterface& operator=(const NativeInterface&) = delete;
    
    // 本地方法注册表
    std::unordered_map<std::string, NativeMethod> nativeMethods;
    
    // 生成方法的唯一标识符
    std::string getMethodKey(const std::string& className,
                           const std::string& methodName,
                           const std::string& descriptor);
};

} // namespace mini_jvm

#endif // MINI_JVM_NATIVE_INTERFACE_H 