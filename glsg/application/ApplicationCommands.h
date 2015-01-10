#ifndef GLSG_APPLICATIONCOMMANDS_H
#define GLSG_APPLICATIONCOMMANDS_H

#include <command/Command.h>
#include <core/Object.h>

namespace glsg {

class ApplicationQuitCommand : public Command {
public:
    virtual void run(Object *obj) {
        static_cast<Application *>(obj)->stop();
    }
};

}

#endif
