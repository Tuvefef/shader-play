#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cgm/cgm.h>

#include <shaderplay/shaderplay.h>

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ShaderWindow sw = sCreateWindow(gmVec2(400, 400), "shader play");
    ShaderProgram sp = sCreateShaderProgram("shaders/ray.vert", "shaders/ray.frag");

    gCacheUniforms(&sp);

    unsigned int gVertexArrayObject;

    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    int w, h;
    glfwGetFramebufferSize(sw.window, &w, &h);
    glfwSetWindowUserPointer(sw.window, &sp);

    while (!glfwWindowShouldClose(sw.window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(sp.gShaderProgram);
        GERR();
        
        gUniformVec3(&sp.u.gColorLoc, gmVec3(0.65f, 0.51f, 0.74f));
        GERR();

        gUniformVec2(&sp.u.gResolutionLoc, gmVec2((float)w, (float)h));
        GERR();

        gUniformFloat(&sp.u.gTimeLoc, (float)glfwGetTime());
        GERR();

        glBindVertexArray(gVertexArrayObject);
        GERR();

        glDrawArrays(GL_TRIANGLES, 0, 3);
        GERR();

        glfwSwapBuffers(sw.window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &gVertexArrayObject);
    sDeleteShaderProgram(&sp);

    sDestroyWindow(&sw);
    glfwTerminate();
}