#ifndef GLSG_PYTHONSCRIPT_H
#define GLSG_PYTHONSCRIPT_H

#include <string>

#include <script/PythonScriptCore.h>
#include <log/Log.h>

namespace glsg {

template<class T>
class PythonScript {
public:
    typedef std::shared_ptr<PythonScript<T>> Ptr;

    PythonScript(const std::string &scriptFile, T *owner) {
        _name = scriptFile.substr(0, scriptFile.length());
        _owner = owner;

        LINFO("Alloc " << _name);

        _module = PythonScriptCore::get()->loadScript(scriptFile);

        LINFO("Will call init");
        call_init();
    }

    ~PythonScript() {
        LINFO("Dealloc " << _name);
    }

    void call_init() {
        try {
            std::string call_symbol = "init_" + _name;

            LDEBUG("Will call " << call_symbol);

            boost::python::object callable = _module.attr(call_symbol.c_str());
            callable(boost::ref(_owner));

            LDEBUG("Done calling " << call_symbol);
        } catch (boost::python::error_already_set) {
            LFATAL("Error");
            PyErr_Print();
            boost::python::throw_error_already_set();
        }
    }

    void call_update(double dt) {
        try {
            std::string call_symbol = "update_" + _name;

            LDEBUG("Will call " << call_symbol);

            boost::python::object callable = _module.attr(call_symbol.c_str());
            callable(boost::ref(_owner), dt);

            LDEBUG("Done calling " << call_symbol);
        } catch (boost::python::error_already_set) {
            LFATAL("Error");
            PyErr_Print();
            boost::python::throw_error_already_set();
        }
    }

private:
    boost::python::object _module;
    std::string _name;
    T *_owner;
};

}

#endif
