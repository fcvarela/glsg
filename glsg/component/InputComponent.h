#ifndef GLSG_INPUTCOMPONENT_H
#define GLSG_INPUTCOMPONENT_H

#include <memory>
#include <vector>
#include <command/Command.h>
#include <log/Log.h>
#include <input/InputListener.h>

namespace glsg {

class Object;

class InputComponent {
public:
    typedef std::shared_ptr<InputComponent> Ptr;

    virtual ~InputComponent() {
        LINFO("Dealloc");
    }

    virtual Command::Vec run(Object *obj, double dt) = 0;
};

}

#endif
