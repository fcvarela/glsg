from camera import Camera
from scene import Scene
from scene_node import SceneNode
from render_state import State

assert Camera
assert Scene
assert SceneNode
assert State


def init_mainmenu_scene(mainMenuScene):
    # create scenegraph
    rootNode = SceneNode("root")
    cameraNode = SceneNode("camera")
    otherNode = SceneNode("other")

    # create topology
    rootNode.addChild(cameraNode)
    rootNode.addChild(otherNode)

    # create the camera
    camera = Camera(45.0, 1.0, 10.0)

    # set the camera's scene node (positioning)
    camera.setSceneNode(cameraNode)

    # create the camera
    camera = Camera(45.0, 1.0, 100.0)
    camera.setClearMode(Camera.GL_COLOR_BUFFER_BIT | Camera.GL_DEPTH_BUFFER_BIT)

    # set the camera's scene node (positioning)
    camera.setSceneNode(cameraNode)

    # set the scene camera
    mainMenuScene.setCamera("mainCamera", camera)
    mainMenuScene.setSceneGraph(rootNode)