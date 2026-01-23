#include "../include/shaderplay/shaderplay.h"

void sFramebufferSizeCallBack(GLFWwindow* sWindow, int w, int h)
{
    (void)sWindow;
    glViewport(0, 0, w, h);
}

ShaderWindow sCreateWindow(vec2 windowSize, const char* windowName)
{
    ShaderWindow gWindow = {
        .w = (int)windowSize.x,
        .h = (int)windowSize.y
    };

    gWindow.gw = glfwCreateWindow(gWindow.w, gWindow.h, windowName, NULL, NULL);

    if (!gWindow.gw)
    {
        printf("failed to create window!\n");
        glfwTerminate();
        return SWNULL;
    }

    glfwMakeContextCurrent(gWindow.gw);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("failed to load GL!\n");
        return SWNULL;
    }

    glfwSetFramebufferSizeCallback(gWindow.gw, sFramebufferSizeCallBack);

    return gWindow;
}

void sMainLoop(vec4 windowColor, ShaderWindow* gw)
{
    while (!glfwWindowShouldClose(gw->gw))
    {
        glClearColor(windowColor.x, windowColor.y, windowColor.z, windowColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(gw->gw);
        glfwPollEvents();
    }
}

void sDestroyWindow(ShaderWindow* gw)
{
    if (gw && gw->gw)
    {
        glfwDestroyWindow(gw->gw);
    }
}