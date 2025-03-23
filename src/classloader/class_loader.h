#ifndef MINI_JVM_CLASS_LOADER_H
#define MINI_JVM_CLASS_LOADER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

namespace mini_jvm {

struct ClassFile {
    uint32_t magic;
    uint16_t minor_version;
    uint16_t major_version;
    std::vector<uint8_t> constant_pool;
    uint16_t access_flags;
    uint16_t this_class;
    uint16_t super_class;
    std::vector<uint16_t> interfaces;
    std::vector<uint8_t> fields;
    std::vector<uint8_t> methods;
    std::vector<uint8_t> attributes;
};

class ClassLoader {
public:
    ClassLoader();
    ~ClassLoader();

    // 加载类文件
    std::shared_ptr<ClassFile> loadClass(const std::string& className);
    
private:
    // 解析类文件
    std::shared_ptr<ClassFile> parseClassFile(const std::vector<uint8_t>& classData);
    
    // 已加载的类缓存
    std::unordered_map<std::string, std::shared_ptr<ClassFile>> loadedClasses;
};

} // namespace mini_jvm

#endif // MINI_JVM_CLASS_LOADER_H 