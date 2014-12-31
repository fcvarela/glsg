#ifndef GLSG_STATEMACHINE_H
#define GLSG_STATEMACHINE_H

#include <stack>
#include <core/StateMachineState.h>

namespace glsg {

class StateMachine {
public:

    inline void pushState(StateMachineState::Ptr state) {
        _stateStack.push(state);
    }

    inline void popState() {
        _stateStack.pop();
    }

    inline StateMachineState::Ptr currentState() {
        return _stateStack.top();
    }

    virtual void update(double dt) = 0;

private:
    std::stack<StateMachineState::Ptr> _stateStack;
};

}

#endif
