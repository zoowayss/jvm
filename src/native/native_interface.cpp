#include "native_interface.h"
#include <stdexcept>

namespace mini_jvm {

NativeInterface& NativeInterface::getInstance() {
    static NativeInterface instance;
    return instance;
}

void NativeInterface::registerNativeMethod(const std::string& className,
                                         const std::string& methodName,
                                         const std::string& descriptor,
                                         NativeMethod method) {
    std::string key = getMethodKey(className, methodName, descriptor);
    nativeMethods[key] = std::move(method);
}

JavaValue NativeInterface::callNativeMethod(const std::string& className,
                                          const std::string& methodName,
                                          const std::string& descriptor,
                                          const std::vector<JavaValue>& args) {
    std::string key = getMethodKey(className, methodName, descriptor);
    
    auto it = nativeMethods.find(key);
    if (it == nativeMethods.end()) {
        throw std::runtime_error("Native method not found: " + key);
    }
    
    return it->second(args);
}

std::string NativeInterface::getMethodKey(const std::string& className,
                                        const std::string& methodName,
                                        const std::string& descriptor) {
    return className + "." + methodName + descriptor;
}

} // namespace mini_jvm 