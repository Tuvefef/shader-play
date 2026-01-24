#include "../include/shaderplay/shader.h"

char *sReadShader(const char *shaderPath)
{
    FILE *shaderFile = fopen(shaderPath, "rb");

    fseek(shaderFile, 0, SEEK_END);
    long codeSize = ftell(shaderFile);
    rewind(shaderFile);

    char *shaderData = malloc(codeSize + 1);
    fread(shaderData, 1, codeSize, shaderFile);
    shaderData[codeSize] = 0;

    fclose(shaderFile);
    return shaderData;
}

void sCheckShaderCompile(unsigned int shader, const char *name)
{
    int shaderSuccess;
    char shaderLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderSuccess);
    if (!shaderSuccess)
    {
        glGetShaderInfoLog(shader, 1024, NULL, shaderLog);
        printf("[SHADER COMPILE ERROR] %s\n%s\n", name, shaderLog);
    }
}

ShaderProgram sCreateShaderProgram(const char *vertexSource, const char *fragmentsource)
{
    ShaderProgram gShader = {
        .gShaderProgram = glCreateProgram()
    };

    unsigned int gVertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int gFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *gVertexShaderSource = sReadShader(vertexSource);
    const char *gFragmentShaderSource = sReadShader(fragmentsource);

    glShaderSource(gVertexShader, 1, &gVertexShaderSource, NULL);
    glShaderSource(gFragmentShader, 1, &gFragmentShaderSource, NULL);

    glCompileShader(gVertexShader);
    glCompileShader(gFragmentShader);

    sCheckShaderCompile(gVertexShader, ":vertex:");
    sCheckShaderCompile(gFragmentShader, ":fragment:");

    glAttachShader(gShader.gShaderProgram, gVertexShader);
    glAttachShader(gShader.gShaderProgram, gFragmentShader);
    glLinkProgram(gShader.gShaderProgram);

    free((void*)gVertexShaderSource);
    free((void*)gFragmentShaderSource);

    glDeleteShader(gVertexShader);
    glDeleteShader(gFragmentShader);

    return gShader;
}

void sDeleteShaderProgram(ShaderProgram *gs)
{
    glDeleteProgram(gs->gShaderProgram);
}