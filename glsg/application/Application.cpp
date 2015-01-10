#include <application/Application.h>
#include <shader/ShaderRegistry.h>
#include <input/InputListener.h>
#include <script/ScriptBridge.h>

namespace glsg {

Application::Application(uint32_t width, uint32_t height, bool fullscreen) {
    LINFO("Application allocating");

    // set our running flag
    _wantsStop = false;

    // initialize graphics so we can call into gl
    glsg::graphics::initialize();

    // create our context
    if (!fullscreen) {
        glsg::graphics::makeWindowContext(width, height);
    } else {
        glsg::graphics::makeFullscreenContext();
    }

    // init input handler
    glsg::InputListener::initialize();

    // initialize scripting
    ScriptBridge::initialize();
}

Application::~Application() {
    LINFO("Application dealloc");
    glsg::graphics::shutdown();
}

void Application::update(double dt) {
    // fixme: this belongs in a background synchronized gpu task
    ShaderRegistry::get()->updateShaders();

    // run our component updates
    for (auto cmd: _inputComponent->run(this, dt)) {
        cmd->run(this);
    }

    // passthrough
    _sceneManager->update(dt);

    // run cull-draw
    _sceneManager->cull();
    _sceneManager->draw();
}

void Application::start() {
    // start assuming we're locked to vsync on a 60Hz display
    double dt = 1.0 / 60.0;
    double start = glsg::graphics::dt();
    double end;

    do {
        // get input
        glsg::InputListener::poll();

        // run update-cull-clear-draw
        update(dt);

        // Swap buffers
        glsg::graphics::swapBuffers();

        // compute time delta
        end = glsg::graphics::dt();
        dt = end - start;

        // safe-guard for breakpoints
        if (dt > 1.0 / 10.0) {
            dt = 1.0 / 60.0;
        }

        // rotate time
        start = end;
    } while (!_wantsStop);
}

void Application::stop() {
    _wantsStop = true;
}

}
