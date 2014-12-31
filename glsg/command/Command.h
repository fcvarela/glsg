#ifndef GLSG_COMMAND_H
#define GLSG_COMMAND_H

#include <log/Log.h>

namespace glsg {

class Command {
public:
    typedef std::shared_ptr<Command> Ptr;

    virtual ~Command() {
        LINFO("Dealloc");
    }

    virtual void run(Object *obj) = 0;
};

}

#endif
