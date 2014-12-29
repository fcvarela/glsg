#ifndef GLSG_RESOURCELOADER_H
#define GLSG_RESOURCELOADER_H

#include <vector>
#include <string>
#include <memory>
#include <mutex>
#include <list>

#include <log/Log.h>

namespace glsg {

class ResourceLoader {
public:

    struct Resource {
        std::string fullpath;
        size_t size;
        const char *data;

        ~Resource() {
            LDEBUG("Resource " << fullpath << " dealloc");
            delete data;
        }
    };

    /**
    * Returns singleton instance.
    */
    static ResourceLoader *get() {
        static ResourceLoader *_instance = new ResourceLoader();
        return _instance;
    }

    /**
    * Registers the base path to load resources from
    * @param path the new path to register.
    */
    void registerBasePath(const std::string &path);

    /**
    * Registers the path inside basePath where to load scripts from.
    */
    void registerScriptPath(const std::string &scriptPath);

    /**
    * Registers the path inside basePath where to load shaders from.
    */
    void registerShaderPath(const std::string &shaderPath);

    /**
    * Registers the path inside basePath where to load models from.
    */
    void registerModelPath(const std::string &modelPath);

    /**
    * Returns base path.
    */
    std::string getBasePath();

    /**
    * Returns script path.
    */
    std::string getScriptPath();


    /**
    * Returns shader path.
    */
    std::string getShaderPath();

    /**
    * Returns model path.
    */
    std::string getModelPath();

    /**
    * Loads and returns the script contents as a c string
    * @param name the script filename
    */
    Resource loadScript(const std::string &name);

    /**
    * Loads and returns the shader contents as a c string
    * @param name the shader filename
    */
    Resource loadShader(const std::string &name);

    /**
    * Loads and returns the model contents as a c string
    * @param name the model filename
    */
    Resource loadModel(const std::string &name);

private:
    /**
    * Holds the base location from which to load resources.
    */
    std::string _basePath;

    /**
    * Hols our list of resource paths.
    */
    std::string _scriptPath;
    std::string _shaderPath;
    std::string _modelPath;

    /**
    * Default constructor.
    */
    ResourceLoader(void) {
        LINFO("ResourceLoader alloc");
    }

    /**
    * Loads a file into a c string and returns it.
    * @param filename the name of the file to load.
    */
    Resource loadFile(const std::string &filename);
};

}

#endif
