#ifndef _GLSG_OBJECT_H
#define _GLSG_OBJECT_H

#include <memory>

namespace glsg {

class Object {
public:
    typedef std::shared_ptr<Object> Ptr;
    typedef std::weak_ptr<Object> WeakPtr;
};

}

#endif