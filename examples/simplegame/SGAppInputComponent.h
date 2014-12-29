#include <glsg/log/Log.h>
#include <glsg/component/InputComponent.h>
#include <glsg/command/Command.h>
#include <glsg/application/ApplicationCommands.h>

using namespace glsg;

class SGAppInputComponent : public InputComponent {
public:
    virtual Command::Ptr run(Object *obj, double dt) {
        auto input = InputListener::getInput();

        if (input->type == Input::KEY && input->key == GLFW_KEY_ESCAPE) {
            // this is a quit command
            return Command::Ptr(new ApplicationQuitCommand());
        }

        return nullptr;
    }
};
