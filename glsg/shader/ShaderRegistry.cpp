#include <regex>
#include <sys/stat.h>

#include <shader/ShaderRegistry.h>

namespace glsg {

Program *ShaderRegistry::loadProgram(const std::string &programFile) {
    // loaded already? return
    if (_programs.find(programFile) != _programs.end()) {
        return _programs[programFile].get();
    }

    auto program = Program::Ptr(new Program(programFile));

    _programs[programFile] = program;
    return program.get();
}

void ShaderRegistry::preprocessShaderResource(ResourceLoader::Resource &res) {
    std::stringstream input;
    input << res.data;

    std::regex include_expr("^[ ]*#[ ]*include[ ]+[\"<](.*)[\">].*");
    std::vector<std::string> outlines;

    std::string line;
    while (std::getline(input, line)) {
        std::smatch match;
        std::regex_search(line, match, include_expr);
        if (match.size() == 0) {
            outlines.push_back(line);
            continue;
        }

        // the match is at index 1, 0 is the full string
        std::string find = match[0].str();
        std::string included_filename = match[1].str();

        LINFO("Will load included file: " << included_filename);
        ResourceLoader::Resource incres = ResourceLoader::get()->loadShader(included_filename);

        // copy new included file data into line vector
        std::stringstream inc_input;
        inc_input << incres.data;
        std::string incline;
        while (std::getline(inc_input, incline)) {
            outlines.push_back(incline);
        }
    }

    // copy outlines into full string output
    std::string output;
    for (size_t i = 0; i < outlines.size(); i++) {
        output += outlines[i] + "\n";
    }
    output = output.substr(0, output.length() - 1);

    // replace resource data pointer with new data
    delete(res.data);
    char *newdata = new char[output.length() + 1];
    memcpy(newdata, output.c_str(), output.length());
    newdata[output.length()] = 0;
    res.data = newdata;
}

Shader *ShaderRegistry::loadShader(const std::string &shaderFile, GLenum shaderType) {
    // we always load the source, might have been reloaded
    ResourceLoader::Resource res = ResourceLoader::get()->loadShader(shaderFile);

    // run #include support preprocessor on data
    preprocessShaderResource(res);

    // create it if it doesn't exist
    if (_shaders.find(shaderFile) == _shaders.end()) {
        _shaders[shaderFile] = Shader::Ptr(new Shader(shaderFile, shaderType));
    }

    // update mtime
    struct stat filestat;
    stat(res.fullpath.c_str(), &filestat);

    struct tm *tm;
    tm = localtime(&filestat.st_mtime);
    _shaders[shaderFile]->setModTime(mktime(tm));

    // reload the source
    _shaders[shaderFile]->updateSource(shaderFile, res.data);

    return _shaders[shaderFile].get();
}

void ShaderRegistry::updateShaders() {
    LDEBUG("ShaderRegistry updateShaders started. Count is " << _programs.size());

    bool changed = false;

    // check which shaders have changed
    for (auto s: _shaders) {
        LDEBUG("ShaderRegistry checking for changes in shader: " << s.second->getName());

        std::string fullpath = ResourceLoader::get()->getBasePath() + "/" + ResourceLoader::get()->getShaderPath() + "/" + s.second->getName();

        struct stat filestat;
        stat(fullpath.c_str(), &filestat);

        struct tm *tm;
        tm = localtime(&filestat.st_mtime);

        uint64_t oldmodtime = s.second->getModTime();
        uint64_t newmodtime = mktime(tm);

        if (newmodtime > oldmodtime) {
            loadShader(s.second->getName(), s.second->getType());
            changed = true;
        }
    }

    // check which programs have updated shaders
    if (!changed) {
        LDEBUG("No changed shaders, will return");
        return;
    }

    for (auto p: _programs) {
        p.second->link();
    }

    LDEBUG("ShaderRegistry updateShaders finished");
}

}
