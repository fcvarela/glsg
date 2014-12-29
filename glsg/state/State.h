#ifndef GLSG_STATE_H
#define GLSG_STATE_H

#include <render/GL.h>

#include <state/Blending.h>
#include <state/Mask.h>
#include <state/CullFace.h>
#include <state/DepthTest.h>
#include <shader/Program.h>
#include <memory>
#include <mutex>

namespace glsg {

class State {
public:
    GLenum frontFace;
    Blending blending;
    Mask mask;
    CullFace cullFace;
    DepthTest depthTest;
    Program *program;

    /**
    * Default constructor, used to set program to nullptr.
    */
    State();

    /**
    * Default dtor for profiling purposes.
    */
    ~State();

    /**
    * Distance calculation, measure state call distance
    * between two states.
    * @param state state to measure distance to
    */
    size_t distance(State &state);

    /**
    * Apply the state and make it active.
    */
    void apply();

    /**
    * Sets the GL state to our known initial state.
    */
    static void setDefault();

    /**
    * Set program
    */
    void setProgram(const std::string &programName);

private:
    /**
    * Stores current state.
    */
    static State _currentState;

};

}

#endif
