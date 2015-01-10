# GLSG
Minimalistic scenegraph rendering toolkit based on GL4.1/GLFW/GLEW/GLM

# Build
GLSG is built using cmake and will place all binaries in a folder named 'build' at the root of the project.

# Dependencies
GLSG needs GLFW3, GLEW, AntTweakBar, OpenGL, OpenCL, libz, Boost, Boost-Python, GLM and Assimp. All of which can be installed using homebrew on a Mac or by running the equivalent of the apt-get statement in the Dockerfile (which I'm using to build for Linux on Mac OS X).

# Usage
While the documents aren't badly out-of-date or scope, it's easier to just check the examples for usage. While everything can be done directly from C++, the examples often use the scripting facilities of GLSG to initialize, update components (scenes and their actors behaviours).

## Simplegame
![alt tag](https://raw.githubusercontent.com/fcvarela/glsg/develop/examples/simplegame/simplegame.png)

This is a minimalistic example which bootstraps from C++ and configures everything using the Python scripting bridge. It displays a model centered on screen, moves the camera back and handles mouse and keyboard input to allow the camera to navigate through the scene. The model is colored with its normal coordinates as color, in eye space.

# Packaging GLSG clients
GLSG can be linked against or compiled into the target directly. In any case, it's always necessary to fix references for libraries it is linked against (aforementioned) when on Mac OS X. Inspect the resulting binaries with otool and use install_name_tool to point to packaged copies of those libraries. Also, because of a nasty bug with GLFW3, anything built on a Mac will have broken retina support unless it is bundled. Yet another reason to package it all together and fix the linking.
