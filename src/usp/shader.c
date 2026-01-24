#include "../include/shaderplay/shader.h"

ShaderSource sReadShader(const char *shaderPath)
{
    ShaderSource src = {
        .shaderPath = shaderPath
    };

    FILE *shaderFile = fopen(src.shaderPath, "rb");
    if (!shaderFile)
    {
        printf("shader error! could not open\n");
        return VOIDSTRC(ShaderSource);
    }

    fseek(shaderFile, 0, SEEK_END);
    src.shaderSize = ftell(shaderFile);
    rewind(shaderFile);

    src.shaderData = malloc(src.shaderSize + 1);
    fread(src.shaderData, 1, src.shaderSize, shaderFile);
    src.shaderData[src.shaderSize] = 0;

    fclose(shaderFile);
    return src;
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

void sDeleteShaderSource(ShaderSource *src)
{
    free(src->shaderData);
    src->shaderData = NULL;
}

ShaderProgram sCreateShaderProgram(const char *vertexSource, const char *fragmentsource)
{
    ShaderProgram gShader = {
        .gShaderProgram = glCreateProgram()
    };

    unsigned int gVertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int gFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    gShader.gVertexShaderSource = sReadShader(vertexSource);
    gShader.gFragmentShaderSource = sReadShader(fragmentsource);

    glShaderSource(gVertexShader, 1, (const char**)&gShader.gVertexShaderSource.shaderData, NULL);
    glShaderSource(gFragmentShader, 1, (const char**)&gShader.gFragmentShaderSource.shaderData, NULL);

    glCompileShader(gVertexShader);
    glCompileShader(gFragmentShader);

    sCheckShaderCompile(gVertexShader, ":vertex:");
    sCheckShaderCompile(gFragmentShader, ":fragment:");

    glAttachShader(gShader.gShaderProgram, gVertexShader);
    glAttachShader(gShader.gShaderProgram, gFragmentShader);
    glLinkProgram(gShader.gShaderProgram);

    sDeleteShaderSource(&gShader.gVertexShaderSource);
    sDeleteShaderSource(&gShader.gFragmentShaderSource);

    glDeleteShader(gVertexShader);
    glDeleteShader(gFragmentShader);

    return gShader;
}

void sDeleteShaderProgram(ShaderProgram *gs)
{
    glDeleteProgram(gs->gShaderProgram);
}