#include "class_loader.h"
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>
// 避免使用filesystem，因为它在某些老版本Linux环境中可能不可用
#include <sys/stat.h>

namespace mini_jvm {

ClassLoader::ClassLoader() {}

ClassLoader::~ClassLoader() {}

// 辅助函数：检查文件是否存在
bool fileExists(const std::string& path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

std::shared_ptr<ClassFile> ClassLoader::loadClass(const std::string& className) {
    // 检查类是否已经加载
    auto it = loadedClasses.find(className);
    if (it != loadedClasses.end()) {
        return it->second;
    }

    // 构造类文件路径
    std::string classPath = className;
    // 替换包路径中的点为目录分隔符（处理跨平台）
    std::replace(classPath.begin(), classPath.end(), '.', '/');
    classPath += ".class";

    // 尝试多个可能的路径
    std::vector<std::string> searchPaths = {
        classPath,                // 当前目录
        "./" + classPath,         // 显式当前目录
        "../" + classPath,        // 上级目录
        "../../" + classPath,     // 再上级目录
    };

    std::string foundPath;
    for (const auto& path : searchPaths) {
        std::cout << "尝试加载类文件: " << path << std::endl;
        if (fileExists(path)) {
            foundPath = path;
            std::cout << "成功找到类文件: " << path << std::endl;
            break;
        }
    }

    if (foundPath.empty()) {
        throw std::runtime_error("无法找到类文件: " + classPath);
    }

    // 读取文件内容
    std::ifstream file(foundPath, std::ios::binary);
    if (!file) {
        throw std::runtime_error("无法打开类文件: " + foundPath);
    }

    std::vector<uint8_t> classData((std::istreambuf_iterator<char>(file)),
                                  std::istreambuf_iterator<char>());
    file.close();

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
        throw std::runtime_error("无效的类文件格式");
    }

    // 读取魔数
    classFile->magic = (classData[0] << 24) | (classData[1] << 16) |
                      (classData[2] << 8)  | classData[3];
    
    if (classFile->magic != 0xCAFEBABE) {
        throw std::runtime_error("无效的类文件魔数");
    }

    // 读取版本号
    classFile->minor_version = (classData[4] << 8) | classData[5];
    classFile->major_version = (classData[6] << 8) | classData[7];

    // TODO: 实现完整的类文件解析
    // 这里简化了很多细节，实际实现需要解析常量池、接口、字段、方法等

    return classFile;
}

} // namespace mini_jvm 