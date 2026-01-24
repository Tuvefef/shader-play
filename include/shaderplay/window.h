#ifndef SHADER_PLAY_WINDOW_H
#define SHADER_PLAY_WINDOW_H

#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cgm/cgm.h>

#define VOIDSTRC(x) ((x){0})

typedef struct 
{
    int w;
    int h;
    GLFWwindow *window;
} ShaderWindow;

ShaderWindow sCreateWindow(vec2 windowSize, const char *windowName);
void sDestroyWindow(ShaderWindow *gw);

#endif