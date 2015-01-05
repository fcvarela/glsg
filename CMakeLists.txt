cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(glsg)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(BUILD_SHARED_LIBS OFF)
add_definitions("-Wno-undefined-inline")

if (APPLE)
    set(CMAKE_PREFIX_PATH /usr/local)
endif(APPLE)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/lib")

set(GLSG_LIBRARY_NAME "glsg")

list (APPEND GLSG_SOURCES
    glsg/application/Application.cpp
    glsg/application/ApplicationCommands.h
    glsg/command/Command.h
    glsg/component/InputComponent.h
    glsg/core/Core.cpp
    glsg/external/imgui/imgui.cpp
    glsg/input/InputListener.cpp
    glsg/log/Log.cpp
    glsg/render/Camera.cpp
    glsg/render/Framebuffer.cpp
    glsg/render/GL.cpp
    glsg/render/Mesh.cpp
    glsg/render/MeshLoader.cpp
    glsg/resource/ResourceLoader.cpp
    glsg/scene/SceneGraphScene.cpp
    glsg/scene/UIScene.cpp
    glsg/scene/SceneManager.cpp
    glsg/scenegraph/SceneNode.cpp
    glsg/scenegraph/SceneNodeCullVisitor.cpp
    glsg/scenegraph/SceneNodeUpdateVisitor.cpp
    glsg/scenegraph/SceneNodeVisitor.cpp
    glsg/script/PythonScript.h
    glsg/script/PythonScriptCore.cpp
    glsg/script/ScriptBridge.cpp
    glsg/shader/Program.cpp
    glsg/shader/Shader.cpp
    glsg/shader/ShaderRegistry.cpp
    glsg/state/Blending.cpp
    glsg/state/Mask.cpp
    glsg/state/CullFace.cpp
    glsg/state/DepthTest.cpp
    glsg/state/State.cpp
)

list (APPEND GLSG_INCLUDE_FILES
    glsg/application/Application.h
    glsg/application/ApplicationCommands.h
    glsg/command/Command.h
    glsg/component/InputComponent.h
    glsg/core/Core.h
    glsg/core/StateMachine.h
    glsg/core/StateMachineState.h
    glsg/external/imgui/imconfig.h
    glsg/external/imgui/imgui.h
    glsg/external/imgui/stb_image.h
    glsg/external/imgui/stb_textedit.h
    glsg/glmext/glmext.h
    glsg/input/Input.h
    glsg/input/ApplicationInputComponent.h
    glsg/input/InputListener.h
    glsg/log/Log.h
    glsg/render/Camera.h
    glsg/render/FrameBuffer.h
    glsg/render/GL.h
    glsg/render/Mesh.h
    glsg/render/MeshLoader.cpp
    glsg/render/RenderState.h
    glsg/render/RenderPass.h
    glsg/resource/ResourceLoader.h
    glsg/scene/Scene.h
    glsg/scene/SceneGraphScene.h
    glsg/scene/UIScene.h
    glsg/scene/SceneManager.h
    glsg/scenegraph/SceneNode.h
    glsg/scenegraph/SceneNodeCullVisitor.h
    glsg/scenegraph/SceneNodeUpdateVisitor.h
    glsg/scenegraph/SceneNodeVisitor.h
    glsg/script/PythonScript.h
    glsg/script/PythonScriptCore.h
    glsg/script/ScriptBridge.h
    glsg/shader/Program.h
    glsg/shader/Shader.h
    glsg/shader/ShaderRegistry.h
    glsg/state/Blending.h
    glsg/state/Mask.h
    glsg/state/CullFace.h
    glsg/state/DepthTest.h
    glsg/state/State.h
)

include_directories(glsg)

# create out target
add_library(${GLSG_LIBRARY_NAME} ${GLSG_SOURCES})

# dependency packages
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)
find_package(GLEW REQUIRED)
find_package(CxxTest REQUIRED)
find_package(PythonInterp 2.7 REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Boost COMPONENTS filesystem system python REQUIRED)

# dependency includes
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${OPENCL_INCLUDE_DIRS})
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${ASSIMP_INCLUDE_DIRS})

MESSAGE(STATUS "CMAKE_SYSTEM_NAME is ${CMAKE_SYSTEM_NAME}")

# apple?
IF(APPLE)
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   FIND_LIBRARY(IOKIT_LIBRARY IOKit)
   FIND_LIBRARY(COREVIDEO_LIBRARY CoreVideo)
   MARK_AS_ADVANCED (COCOA_LIBRARY
                     IOKIT_LIBRARY
                     COREVIDEO_LIBRARY)
   SET(EXTRA_LIBS ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
ENDIF (APPLE)

IF(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    SET(EXTRA_LIBS ${X11_LIBRARIES} ${X11_Xxf86vm_LIB} ${X11_Xrandr_LIB} ${X11_Xinput_LIB} pthread Xcursor Xinerama)
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Linux")

# dependency libraries
target_link_libraries(${GLSG_LIBRARY_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${GLSG_LIBRARY_NAME} ${OPENCL_LIBRARIES})
target_link_libraries(${GLSG_LIBRARY_NAME} ${GLFW_LIBRARIES})
target_link_libraries(${GLSG_LIBRARY_NAME} ${GLEW_LIBRARIES})
target_link_libraries(${GLSG_LIBRARY_NAME} ${ASSIMP_LIBRARIES})
target_link_libraries(${GLSG_LIBRARY_NAME} ${ZLIB_LIBRARIES})
target_link_libraries(${GLSG_LIBRARY_NAME} ${Boost_FILESYSTEM_LIBRARY})
target_link_libraries(${GLSG_LIBRARY_NAME} ${Boost_SYSTEM_LIBRARY})
target_link_libraries(${GLSG_LIBRARY_NAME} ${Boost_PYTHON_LIBRARY})
target_link_libraries(${GLSG_LIBRARY_NAME} ${PYTHON_LIBRARIES})

target_link_libraries(${GLSG_LIBRARY_NAME} ${EXTRA_LIBS})

# install
set(GLSG_LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib)

INSTALL(TARGETS ${GLSG_LIBRARY_NAME} DESTINATION ${GLSG_LIB_INSTALL_DIR})
INSTALL(FILES ${GLSG_INCLUDE_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/${GLSG_LIBRARY_NAME})

# build examples
option(BUILD_EXAMPLES "Build examples" ON)

if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif(BUILD_EXAMPLES)

# build unit tests
add_subdirectory(tests)
