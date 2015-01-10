#include <glsg/log/Log.h>
#include <glsg/component/InputComponent.h>
#include <glsg/command/Command.h>
#include <glsg/application/ApplicationCommands.h>

using namespace glsg;

class SGAppInputComponent : public InputComponent {
public:
    virtual Command::Vec run(Object *obj, double dt) {
        auto input = InputListener::getInput();

        Command::Vec commands;

        if (input->key.valid && input->key.key == GLFW_KEY_ESCAPE) {
            // this is a quit command
            commands.push_back(Command::Ptr(new ApplicationQuitCommand()));
        }

        return commands;
    }
};
