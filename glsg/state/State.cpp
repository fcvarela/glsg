#include <state/State.h>
#include <shader/ShaderRegistry.h>

namespace glsg {

State State::_currentState;

State::State() {
    LINFO("Alloc");
    program = nullptr;
}

State::~State() {
    LINFO("Dealloc");
}

size_t State::distance(State &state) {
    size_t dist = 0;

    dist += blending.distance(state.blending);
    dist += mask.distance(state.mask);
    dist += cullFace.distance(state.cullFace);
    dist += depthTest.distance(state.depthTest);

    if (program != state.program) {
        dist += 1;
    }

    return dist;

}

void State::apply() {
    if (program == nullptr) {
        throw;
    }

    if (program != _currentState.program) {
        program->activate();
    }

    blending.apply(_currentState.blending, false);
    mask.apply(_currentState.mask, false);
    cullFace.apply(_currentState.cullFace, false);
    depthTest.apply(_currentState.depthTest, false);
}

void State::setDefault() {
    _currentState.blending.apply(_currentState.blending, true);
    _currentState.mask.apply(_currentState.mask, true);
    _currentState.cullFace.apply(_currentState.cullFace, true);
    _currentState.depthTest.apply(_currentState.depthTest, true);
}

void State::setProgram(const std::string &programName) {
    program = ShaderRegistry::get()->loadProgram(programName);
}

}
