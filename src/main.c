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
    ShaderProgram sp = sCreateShaderProgram("shaders/core/main.vsh", "shaders/core/main.fsh");
    gCacheUniforms(&sp);

    ShaderProgram post = sCreateShaderProgram("shaders/post/post.vsh", "shaders/post/post.fsh");
    gCacheUniforms(&post);

    unsigned int gVertexArrayObject;
    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    int w, h;
    glfwGetFramebufferSize(sw.window, &w, &h);

    FrameBuffer f0 = gCreateFrameBuffer(w, h);    

    ShaderPointers shp;
    shp.mainShader = &sp;
    shp.postShader = &post;

    glfwSetWindowUserPointer(sw.window, &shp);

    double mx, my;

    while (!glfwWindowShouldClose(sw.window))
    {
        glfwGetFramebufferSize(sw.window, &w, &h);
        glfwGetCursorPos(sw.window, &mx, &my);

        float nmx = mx / w;
        float nmy = 1.0f - (my / h);

        glBindFramebuffer(GL_FRAMEBUFFER, f0.frameBufferObject);
        glViewport(0, 0, w, h);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(sp.gShaderProgram);

        gUniformVec3(&sp.u.gColorLoc, gmVec3(0.65f, 0.51f, 0.74f));
        gUniformVec2(&sp.u.gResolutionLoc, gmVec2((float)w, (float)h));
        gUniformFloat(&sp.u.gTimeLoc, (float)glfwGetTime());
        gUniformVec2(&sp.u.gMouse, gmVec2(nmx, nmy));

        glBindVertexArray(gVertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, w, h);

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(post.gShaderProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, f0.frameBufferTexture);
        glUniform1i(post.u.gScene.uloc, 0);

        glBindVertexArray(gVertexArrayObject);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(sw.window);
        glfwPollEvents();
    }

    gDeleteFrameBuffer(&f0);
    glDeleteTextures(1, &f0.frameBufferTexture);
    glDeleteVertexArrays(1, &gVertexArrayObject);

    sDeleteShaderProgram(&sp);
    sDestroyWindow(&sw);
    glfwTerminate();

    return 0;
}
