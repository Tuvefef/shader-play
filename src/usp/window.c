#include "../include/shaderplay/uniform.h"
#include "../include/shaderplay/spointer.h"
#include "../include/shaderplay/debug.h"
#include "../include/shaderplay/window.h"

static void sFramebufferSizeCallBack(GLFWwindow *window, int w, int h)
{
    glViewport(0, 0, w, h);

    ShaderProgram *s = glfwGetWindowUserPointer(window);
    if(s)
    {
        glUseProgram(s->gShaderProgram);
        GERR();

        gUniformVec2(&s->u.gResolutionLoc, gmVec2((float)w, (float)h));
    }
}

static void sKeyCallBack(GLFWwindow *window, int k, int s, int a, int m)
{
    (void)s;
    (void)m;

    if (k == GLFW_KEY_R && a == GLFW_PRESS)
    {
        ShaderPointers *shaders = glfwGetWindowUserPointer(window);
        if(shaders) {
            sReloadShaderProgram(shaders->mainShader);
            sReloadShaderProgram(shaders->postShader);
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
        GLOG("failed to create window");
        glfwTerminate();
        return VOIDSTRC(ShaderWindow);
    }

    glfwMakeContextCurrent(gWindow.window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        GLOG("failed to load GL");
        return VOIDSTRC(ShaderWindow);
    }

    int fbw, fbh;
    glfwGetFramebufferSize(gWindow.window, &fbw, &fbh);
    glViewport(0, 0, fbw, fbh);

    glfwSetFramebufferSizeCallback(gWindow.window, sFramebufferSizeCallBack);
    glfwSetKeyCallback(gWindow.window, sKeyCallBack);

    return gWindow;
}

void sDestroyWindow(ShaderWindow *gw)
{
    glfwDestroyWindow(gw->window);
}