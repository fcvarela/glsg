#ifndef GLSG_STATATEMACHINESTATE_H
#define GLSG_STATATEMACHINESTATE_H

namespace glsg {

class StateMachineState {
public:
    typedef std::shared_ptr<StateMachineState> Ptr;

    virtual void activate() = 0;

    virtual void deactivate() = 0;

    virtual void update(double dt) = 0;
};

}

#endif
