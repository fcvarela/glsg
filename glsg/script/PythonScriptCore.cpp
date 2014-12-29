#include <boost/filesystem.hpp>
#include <resource/ResourceLoader.h>
#include <script/PythonScriptCore.h>

namespace glsg {

using namespace boost::python;

PythonScriptCore::PythonScriptCore() {
    LINFO("PythonScriptCore alloc");
    try {
        LINFO("Will initialize python");
        Py_Initialize();

        LINFO("Will create main module");
        _module = object(handle<>(borrowed(PyImport_AddModule("__main__"))));

        LINFO("Will set global state dict");
        _global = _module.attr("__dict__");

        LINFO("Will register package path");
        boost::filesystem::path workingDir = boost::filesystem::absolute(
                ResourceLoader::get()->getBasePath() + "/" + ResourceLoader::get()->getScriptPath()).normalize();

        PyObject *sysPath = PySys_GetObject((char *) "path");
        PyList_Insert(sysPath, 0, PyString_FromString(workingDir.string().c_str()));

        LINFO("Registered package path: " << workingDir.string());

        // Load the sys module.
        object sys = object(handle<>(borrowed(PyImport_ImportModule("sys"))));

        // Extract the python version.
        std::string version = extract<std::string>(sys.attr("version"));
        LINFO("Python: " << version);
    } catch (error_already_set) {
        LFATAL("Error loading script");
        PyErr_Print();
        throw_error_already_set();
    }
}

object PythonScriptCore::loadScript(const std::string &scriptFile) {
    LINFO("Will import " << scriptFile);

    try {
        object module = object(handle<>(borrowed(PyImport_ImportModule(scriptFile.c_str()))));
        return module;
    } catch (error_already_set) {
        LFATAL("Error loading script");
        PyErr_Print();
        throw_error_already_set();
        return object();
    }
}

PythonScriptCore::~PythonScriptCore() {
    LINFO("PythonScriptCore dealloc");
}

}
