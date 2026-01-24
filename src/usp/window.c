#include "../include/shaderplay/shaderplay.h"

void sFramebufferSizeCallBack(GLFWwindow *window, int w, int h)
{
    (void)window;
    glViewport(0, 0, w, h);
}

ShaderWindow sCreateWindow(vec2 windowSize, const char *windowName)
{
    ShaderWindow gWindow = {
        .w = (int)windowSize.x,
        .h = (int)windowSize.y
    };

    gWindow.window = glfwCreateWindow(gWindow.w, gWindow.h, windowName, NULL, NULL);

    if (!gWindow.window)
    {
        printf("failed to create window!\n");
        glfwTerminate();
        return SWNULL;
    }

    glfwMakeContextCurrent(gWindow.window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("failed to load GL!\n");
        return SWNULL;
    }

    glfwSetFramebufferSizeCallback(gWindow.window, sFramebufferSizeCallBack);

    return gWindow;
}

void sDestroyWindow(ShaderWindow *gw)
{
    if (gw && gw->window)
    {
        glfwDestroyWindow(gw->window);
    }
}