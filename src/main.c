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
    ShaderProgram sp = sCreateShaderProgram("shaders/core.vert", "shaders/core.frag");

    unsigned int gVertexArrayObject;

    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    while (!glfwWindowShouldClose(sw.window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(sp.gShaderProgram);
        glBindVertexArray(gVertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        GLERR();

        glfwSwapBuffers(sw.window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &gVertexArrayObject);
    sDeleteShaderProgram(&sp);

    sDestroyWindow(&sw);
    glfwTerminate();
}