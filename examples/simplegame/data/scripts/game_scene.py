from camera import Camera
from scene import Scene
from scene_node import SceneNode
from render_state import State

assert Camera
assert Scene
assert SceneNode
assert State


def init_game_scene(gameScene):
    # create scenegraph
    rootNode = SceneNode("root")
    cameraNode = SceneNode("camera")
    cowNode = SceneNode("cow")

    # load cow model
    cowNode.loadMesh("cow.obj")
    cowNode.getState().setProgram("cow_program")

    # pull camera back
    cameraNode.translate(0.0, 0.0, -20.0)

    # create topology
    rootNode.addChild(cameraNode)
    rootNode.addChild(cowNode)

    # create the camera
    camera = Camera(45.0, 1.0, 100.0)
    camera.setClearMode(Camera.GL_COLOR_BUFFER_BIT | Camera.GL_DEPTH_BUFFER_BIT)

    # set the camera's scene node (positioning)
    camera.setSceneNode(cameraNode)

    # set the scene camera
    gameScene.setCamera("mainCamera", camera)
    gameScene.setSceneGraph(rootNode)
