#ifndef SHADER_PLAY_WINDOW_H
#define SHADER_PLAY_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cgm/cgm.h>

#include <stdio.h>

#define SWNULL (ShaderWindow){0}

typedef struct 
{
    int w;
    int h;
    GLFWwindow* gw;
} ShaderWindow;

ShaderWindow sCreateWindow(vec2 windowSize, const char* windowName);

void sMainLoop(vec4 windowColor, ShaderWindow* gw);
void sDestroyWindow(ShaderWindow* gw);

#endif