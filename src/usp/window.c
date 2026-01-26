#include "../include/shaderplay/shaderplay.h"

static void sFramebufferSizeCallBack(GLFWwindow *window, int w, int h)
{
    (void)window;
    glViewport(0, 0, w, h);
}

static void sKeyCallBack(GLFWwindow *window, int k, int s, int a, int m)
{
    (void)m;
    (void)s;

    if (k == GLFW_KEY_R && a == GLFW_PRESS)
    {
        ShaderProgram *shader = glfwGetWindowUserPointer(window);
        if (shader)
        {
            sReloadShaderProgram(shader);
        }
    }
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
        fprintf(stderr, "failed to create window!\n");
        glfwTerminate();
        return VOIDSTRC(ShaderWindow);
    }

    glfwMakeContextCurrent(gWindow.window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        fprintf(stderr, "failed to load GL!\n");
        return VOIDSTRC(ShaderWindow);
    }

    glfwSetFramebufferSizeCallback(gWindow.window, sFramebufferSizeCallBack);
    glfwSetKeyCallback(gWindow.window, sKeyCallBack);

    return gWindow;
}

void sDestroyWindow(ShaderWindow *gw)
{
    glfwDestroyWindow(gw->window);
}