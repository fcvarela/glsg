#include <glsg/log/Log.h>
#include <glsg/resource/ResourceLoader.h>

using namespace glsg;

int App_main();

int main(int argc, char **argv) {
    // setup main logger
    glsg::Log::AppLogLevel = glsg::Log::DEBUG;

    // initialize resource
    // global resource locations. make sure you call this in your app
    // tip, you can load the values from the environment
    glsg::ResourceLoader::get()->registerBasePath("data");
    glsg::ResourceLoader::get()->registerScriptPath("scripts");
    glsg::ResourceLoader::get()->registerShaderPath("shaders");
    glsg::ResourceLoader::get()->registerModelPath("models");

    // run app
    return App_main();
}
