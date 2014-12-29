#ifndef GLSG_PYTHONSCRIPTCORE_H
#define GLSG_PYTHONSCRIPTCORE_H

#include <string>
#include <memory>
#include <mutex>

#include <boost/python.hpp>

#include <log/Log.h>

namespace glsg {

/**
* @defgroup script script
* @ingroup glsg
* Scripting support.
*/

/**
* The ScriptCore singleton is used to load script files and register C++
* class bindings, making them available to the global Python state.
* @ingroup script
*/
class PythonScriptCore {
public:
    /**
    * Returns the singleton instance
    */
    static PythonScriptCore *get() {
        static PythonScriptCore *_instance = new PythonScriptCore();
        return _instance;
    }

    ~PythonScriptCore();

    /**
    * Loads a script into the global state. Functions will be made available.
    * @param scriptFile the script file to load.
    */
    boost::python::object loadScript(const std::string &scriptFile);

private:
    /**
    * Private constructor to prevent foreign instantiation.
    */
    PythonScriptCore();

    /**
    * Main Python namespace
    */
    boost::python::object _global;
    boost::python::object _module;
};

}

#endif
