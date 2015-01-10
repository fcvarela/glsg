#include <glsg/log/Log.h>
#include <glsg/component/InputComponent.h>

using namespace glsg;

class SGSceneManagerInputComponent : public InputComponent {
public:
    virtual Command::Vec run(Object *obj, double dt) {
        return Command::Vec();
    }
};
