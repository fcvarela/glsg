#include <glsg/log/Log.h>
#include <glsg/component/InputComponent.h>
#include <glsg/command/Command.h>
#include <glsg/render/CameraCommands.h>

using namespace glsg;

class SGCameraInputComponent : public InputComponent {
public:
    virtual Command::Vec run(Object *obj, double dt) {
        auto input = InputListener::getInput();

        Command::Vec commands;

        if (input->key.active[GLFW_KEY_W]) {
            commands.push_back(Command::Ptr(new CameraMoveCommand(glm::dvec3(0.0, 0.0, -2.0) * dt)));
        }

        if (input->key.active[GLFW_KEY_S]) {
            commands.push_back(Command::Ptr(new CameraMoveCommand(glm::dvec3(0.0, 0.0, 2.0) * dt)));
        }

        if (input->key.active[GLFW_KEY_A]) {
            commands.push_back(Command::Ptr(new CameraMoveCommand(glm::dvec3(-2.0, 0.0, 0.0) * dt)));
        }

        if (input->key.active[GLFW_KEY_D]) {
            commands.push_back(Command::Ptr(new CameraMoveCommand(glm::dvec3(2.0, 0.0, 0.0) * dt)));
        }

        if (input->key.active[GLFW_KEY_Q]) {
            commands.push_back(Command::Ptr(new CameraMoveCommand(glm::dvec3(0.0, 2.0, 0.0) * dt)));
        }

        if (input->key.active[GLFW_KEY_Z]) {
            commands.push_back(Command::Ptr(new CameraMoveCommand(glm::dvec3(0.0, -2.0, 0.0) * dt)));
        }

        if (input->mouseMove.valid) {
            commands.push_back(Command::Ptr(
                    new CameraRotateCommand(glm::dvec3(-1.0, 0.0, 0.0), input->mouseMove.dist_y/100.0)));

            commands.push_back(Command::Ptr(
                    new CameraRotateCommand(glm::dvec3(0.0, -1.0, 0.0), input->mouseMove.dist_x/100.0)));
        }

        return commands;
    }
};
