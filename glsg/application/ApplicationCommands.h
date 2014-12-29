#ifndef _GLSG_APPLICATIONQUITCOMMAND_H
#define _GLSG_APPLICATIONQUITCOMMAND_H

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
