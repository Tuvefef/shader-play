#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cgm/cgm.h>

#include <shaderplay/shaderplay.h>

int main()
{
    if (!glfwInit()) 
    {
        printf("failed to init glfw\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ShaderWindow sw = sCreateWindow(gmVec2(400, 400), "shader play");

    sMainLoop(gmVec4(0.2f, 0.3f, 0.4f, 1.0f), &sw);

    sDestroyWindow(&sw);
    glfwTerminate();
}