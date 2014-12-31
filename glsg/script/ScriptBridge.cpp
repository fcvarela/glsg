#include <boost/python.hpp>

#include <application/Application.h>
#include <script/ScriptBridge.h>
#include <shader/ShaderRegistry.h>
#include <scenegraph/SceneNode.h>
#include <render/Camera.h>
#include <scene/SceneGraphScene.h>
#include <scene/UIScene.h>

namespace glsg {

using namespace boost::python;

BOOST_PYTHON_MODULE (scene_node) {
    class_<SceneNode, SceneNode::Ptr>("SceneNode", init<std::string>())
            .def("setActive", &SceneNode::setActive)
            .def("addChild", &SceneNode::addChild)
            .def("removeChild", &SceneNode::removeChild)
            .def("rotate", &SceneNode::rotate)
            .def("translate", &SceneNode::translate)
            .def("loadMesh", &SceneNode::loadMesh)
            .def("getState", &SceneNode::getState, return_value_policy<reference_existing_object>());
};

BOOST_PYTHON_MODULE (shader_registry) {
    class_<ShaderRegistry, boost::noncopyable>("ShaderRegistry", no_init)
            .def("loadShader", &ShaderRegistry::loadShader, return_value_policy<reference_existing_object>())
            .def("loadProgram", &ShaderRegistry::loadProgram, return_value_policy<reference_existing_object>())
            .def("getInstance", &ShaderRegistry::get, return_value_policy<reference_existing_object>())
            .staticmethod("getInstance");
};

BOOST_PYTHON_MODULE (shader) {
    auto shader_class = class_<Shader>("Shader", init<std::string, GLenum>());
    shader_class.attr("GL_COMPUTE_SHADER") = GL_COMPUTE_SHADER;
    shader_class.attr("GL_VERTEX_SHADER") = GL_VERTEX_SHADER;
    shader_class.attr("GL_TESS_CONTROL_SHADER") = GL_TESS_CONTROL_SHADER;
    shader_class.attr("GL_TESS_EVALUATION_SHADER") = GL_TESS_EVALUATION_SHADER;
    shader_class.attr("GL_GEOMETRY_SHADER") = GL_GEOMETRY_SHADER;
    shader_class.attr("GL_FRAGMENT_SHADER") = GL_FRAGMENT_SHADER;
};

BOOST_PYTHON_MODULE (program) {
    class_<Program>("Program", init<std::string>())
            .def("attach", &Program::attach)
            .def("link", &Program::link);
};

BOOST_PYTHON_MODULE (render_state) {
    class_<State>("State", no_init)
            .def("setProgram", &State::setProgram);
};

BOOST_PYTHON_MODULE (log) {
    def("SDEBUG", SDEBUG);
    def("SINFO", SINFO);
    def("SWARNING", SWARNING);
    def("SERROR", SERROR);
    def("SFATAL", SFATAL);
}

BOOST_PYTHON_MODULE (camera) {
    auto camera_class = class_<Camera, Camera::Ptr>("Camera", init<double, double, double>())
            .def("setSceneNode", &Camera::setSceneNode)
            .def("setClearMode", &Camera::setClearMode)
            .def("setViewport", &Camera::setViewport)
            .def("setFramebuffer", &Camera::setFramebuffer);

    camera_class.attr("GL_DEPTH_BUFFER_BIT") = GL_DEPTH_BUFFER_BIT;
    camera_class.attr("GL_COLOR_BUFFER_BIT") = GL_COLOR_BUFFER_BIT;
}

BOOST_PYTHON_MODULE (scene) {
    class_<SceneGraphScene, SceneGraphScene::Ptr>("SceneGraphScene", init<std::string, uint32_t, uint32_t>())
            .def("setCamera", &SceneGraphScene::setCamera)
            .def("setSceneGraph", &SceneGraphScene::setSceneGraph);

    class_<UIScene, UIScene::Ptr>("UIScene", init<std::string, uint32_t, uint32_t>());
}

BOOST_PYTHON_MODULE (framebuffer) {
    class_<Framebuffer, Framebuffer::Ptr>("Framebuffer", init<uint32_t, uint32_t, bool>());
}

BOOST_PYTHON_MODULE (application) {
    class_<Application, Application::Ptr>("Application", init<uint32_t, uint32_t, bool>())
            .def("start", &Application::start);
}

void ScriptBridge::initialize() {
    if (PyImport_AppendInittab("scene_node", initscene_node) == -1) {
        throw std::runtime_error("Failed to register scene_node with interpreter");
    }

    if (PyImport_AppendInittab("shader_registry", initshader_registry) == -1) {
        throw std::runtime_error("Failed to register shader_registry with interpreter");
    }

    if (PyImport_AppendInittab("shader", initshader) == -1) {
        throw std::runtime_error("Failed to register shader with interpreter");
    }

    if (PyImport_AppendInittab("program", initprogram) == -1) {
        throw std::runtime_error("Failed to register program with interpreter");
    }

    if (PyImport_AppendInittab("render_state", initrender_state) == -1) {
        throw std::runtime_error("Failed to register state with interpreter");
    }

    if (PyImport_AppendInittab("log", initlog) == -1) {
        throw std::runtime_error("Failed to register state with interpreter");
    }

    if (PyImport_AppendInittab("camera", initcamera) == -1) {
        throw std::runtime_error("Failed to register camera with interpreter");
    }

    if (PyImport_AppendInittab("scene", initscene) == -1) {
        throw std::runtime_error("Failed to register camera with interpreter");
    }

    if (PyImport_AppendInittab("framebuffer", initframebuffer) == -1) {
        throw std::runtime_error("Failed to register framebuffer with interpreter");
    }

    if (PyImport_AppendInittab("application", initapplication) == -1) {
        throw std::runtime_error("Failed to register application with interpreter");
    }
}

}
