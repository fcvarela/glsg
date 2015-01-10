#ifndef GLSG_COMMAND_H
#define GLSG_COMMAND_H

#include <core/Object.h>
#include <log/Log.h>

namespace glsg {

class Command {
public:
    typedef std::shared_ptr<Command> Ptr;
    typedef std::vector<Ptr> Vec;

    virtual ~Command() {
        LINFO("Dealloc");
    }

    virtual void run(Object *obj) = 0;
};

}

#endif
