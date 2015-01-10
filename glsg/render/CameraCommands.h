#ifndef GLSG_CAMERACOMMANDS_H
#define GLSG_CAMERACOMMANDS_H

#include <core/Object.h>
#include <render/Camera.h>

namespace glsg {

class CameraMoveCommand : public Command {
public:
    CameraMoveCommand(glm::dvec3 travel) :
            _travel(travel) {}

    virtual void run(Object *obj) {
        LDEBUG("Will move camera");
        static_cast<SceneNode *>(obj)->translate(
                _travel.x,
                _travel.y,
                _travel.z);

    }
private:
    glm::dvec3 _travel;
};

class CameraRotateCommand : public Command {
public:
    CameraRotateCommand(glm::vec3 axis, double angle) :
            _axis(axis), _angle(angle) {}

    virtual void run(Object *obj) {
        LDEBUG("Will rotate camera");
        static_cast<SceneNode *>(obj)->rotate(
                _angle, _axis.x, _axis.y, _axis.z);
    }

private:
    glm::vec3 _axis;
    double _angle;
};

}

#endif
