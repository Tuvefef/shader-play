# Shader Play

Shader Play is a project written in C language that is a shading playground created in the wsl ubuntu environment.

With this project you can create or edit your shaders just like in shader toy

## characteristics

- use opengl 3.3 core
- external shader system of .frag and .vert files
- automatic reload of shaders when pressing the R key
- uniforms in real time
- full screen rendering
- frame buffer
- basic `#include` directive for shaders

    example:

    `shaders/util/cube.glsl`:
    ```glsl
    float gRenderCube(vec3 gp, vec2 mouse)
    {
        return length(max(abs(gp) - vec3(0.9) + mouse.x, 0.0));
    }   
    ````
    `shaders/ray.frag`:
    ```glsl
    #include "util/cube.glsl"
    ```

## dependencies

- opengl 3.3 core (glad)(https://glad.dav1d.de/)
- cgm (mathematics for graphs for C)(https://github.com/Tuvefef/cgm)
- glfw (system package) you can install it with this script (`instllglfw.sh`)

## use

*by having the dependencies already installed*

1: in `main.c` connect the shaders folder:
```c
sCreateShaderProgram("shaders/ray.vert", "shaders/ray.frag");
```
They have to be fragment and vertex

2: create the basic uniforms to use in your shader:
```c
gUniformVec2(resolution location, gmVec2((float)w, (float)h));
gUniformFloat(time location, (float)glfwGetTime());
```

3: run makefile

### example shader

**this test shader is ray marching**

![cube ray marching demo](https://github.com/Tuvefef/shader-play/blob/main/img/ray.gif)
