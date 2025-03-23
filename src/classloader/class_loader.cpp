#include "class_loader.h"
#include <fstream>
#include <stdexcept>

namespace mini_jvm {

ClassLoader::ClassLoader() {}

ClassLoader::~ClassLoader() {}

std::shared_ptr<ClassFile> ClassLoader::loadClass(const std::string& className) {
    // 检查类是否已经加载
    auto it = loadedClasses.find(className);
    if (it != loadedClasses.end()) {
        return it->second;
    }

    // 构造类文件路径
    std::string classPath = className;
    std::replace(classPath.begin(), classPath.end(), '.', '/');
    classPath += ".class";

    // 读取类文件
    std::ifstream file(classPath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open class file: " + classPath);
    }

    // 读取文件内容
    std::vector<uint8_t> classData((std::istreambuf_iterator<char>(file)),
                                  std::istreambuf_iterator<char>());

    // 解析类文件
    auto classFile = parseClassFile(classData);
    
    // 缓存并返回
    loadedClasses[className] = classFile;
    return classFile;
}

std::shared_ptr<ClassFile> ClassLoader::parseClassFile(const std::vector<uint8_t>& classData) {
    auto classFile = std::make_shared<ClassFile>();
    
    // 简化版的类文件解析
    if (classData.size() < 8) {
        throw std::runtime_error("Invalid class file format");
    }

    // 读取魔数
    classFile->magic = (classData[0] << 24) | (classData[1] << 16) |
                      (classData[2] << 8)  | classData[3];
    
    if (classFile->magic != 0xCAFEBABE) {
        throw std::runtime_error("Invalid class file magic number");
    }

    // 读取版本号
    classFile->minor_version = (classData[4] << 8) | classData[5];
    classFile->major_version = (classData[6] << 8) | classData[7];

    // TODO: 实现完整的类文件解析
    // 这里简化了很多细节，实际实现需要解析常量池、接口、字段、方法等

    return classFile;
}

} // namespace mini_jvm 