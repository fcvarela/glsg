# coding=utf8

from program import Program
from shader import Shader
from shader_registry import ShaderRegistry

assert Program
assert Shader
assert ShaderRegistry


def init_cow_program(p):
    sri = ShaderRegistry.getInstance()

    c1 = sri.loadShader("include/common.glsl", Shader.GL_VERTEX_SHADER)
    vs = sri.loadShader("basic.vs.glsl", Shader.GL_VERTEX_SHADER)
    fs = sri.loadShader("basic.fs.glsl", Shader.GL_FRAGMENT_SHADER)

    p.attach(c1)
    p.attach(vs)
    p.attach(fs)

    p.link()
