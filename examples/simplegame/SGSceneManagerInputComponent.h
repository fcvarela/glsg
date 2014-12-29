#include <glsg/log/Log.h>
#include <glsg/component/InputComponent.h>

using namespace glsg;

class SGSceneManagerInputComponent : public InputComponent {
public:
    virtual Command::Ptr run(Object *obj, double dt) {
        auto input = InputListener::getInput();
        if (input->type != Input::INVALID) {
            LINFO("WHOOOOOOOOOOOOOOOO");
        }
        return nullptr;
    }
};
