#include <fstream>
#include <resource/ResourceLoader.h>


namespace glsg {

void ResourceLoader::registerBasePath(const std::string &path) {
    _basePath = path;
}

void ResourceLoader::registerScriptPath(const std::string &path) {
    _scriptPath = path;
}

void ResourceLoader::registerShaderPath(const std::string &path) {
    _shaderPath = path;
}

void ResourceLoader::registerModelPath(const std::string &path) {
    _modelPath = path;
}

std::string ResourceLoader::getBasePath() {
    return _basePath;
}

std::string ResourceLoader::getScriptPath() {
    return _scriptPath;
}

std::string ResourceLoader::getShaderPath() {
    return _shaderPath;
}

std::string ResourceLoader::getModelPath() {
    return _modelPath;
}

// fixme: filesystem path separator must be portable, use boost_filesystem here
ResourceLoader::Resource ResourceLoader::loadScript(const std::string &name) {
    std::string path = _basePath + "/" + _scriptPath + "/" + name;
    return loadFile(path);
}

ResourceLoader::Resource ResourceLoader::loadShader(const std::string &name) {
    std::string path = _basePath + "/" + _shaderPath + "/" + name;
    return loadFile(path);
}

ResourceLoader::Resource ResourceLoader::loadModel(const std::string &name) {
    std::string path = _basePath + "/" + _modelPath + "/" + name;
    return loadFile(path);
}

ResourceLoader::Resource ResourceLoader::loadFile(const std::string &name) {
    std::ifstream file(name.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
    std::ifstream::pos_type fileSize;

    char *fileContents = NULL;
    if (file.is_open()) {
        fileSize = file.tellg();
        fileContents = new char[(size_t) fileSize + 1];
        fileContents[fileSize] = 0;
        file.seekg(0, std::ios::beg);

        if (!file.read(fileContents, fileSize)) {
            LFATAL("Cannot read file: " << name);
            throw;
        }

        file.close();
    }

    ResourceLoader::Resource out = {
            .fullpath = name,
            .size = (size_t) fileSize,
            .data = fileContents
    };

    return out;
}

}
