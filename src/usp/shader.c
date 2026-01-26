#include "../include/shaderplay/shader.h"

static ShaderSource sReadShader(const char *shaderPath)
{
    ShaderSource src = {
        .shaderPath = shaderPath
    };

    FILE *shaderFile = fopen(src.shaderPath, "rb");
    if (!shaderFile)
    {
        perror("fopen shader");
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

static void sCheckShaderCompile(unsigned int shader, const char *name)
{
    int shaderSuccess;
    char shaderLog[1024];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderSuccess);
    if (!shaderSuccess)
    {
        glGetShaderInfoLog(shader, 1024, NULL, shaderLog);
        fprintf(stderr, "[SHADER COMPILE ERROR] %s\n%s\n", name, shaderLog);
    }
}

static void sDeleteShaderSource(ShaderSource *src)
{
    free(src->shaderData);
    src->shaderData = NULL;
}

ShaderProgram sCreateShaderProgram(const char *vertexSource, const char *fragmentSource)
{
    ShaderProgram gShader = {
        .gShaderProgram = glCreateProgram(),
        .gVertexShaderPath = vertexSource,
        .gFragmentShaderPath = fragmentSource
    };

    unsigned int gVertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int gFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    gShader.gVertexShaderSource = sReadShader(vertexSource);
    gShader.gFragmentShaderSource = sReadShader(fragmentSource);

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

void sReloadShaderProgram(ShaderProgram *s)
{
    ShaderProgram n = sCreateShaderProgram(s->gVertexShaderPath, s->gFragmentShaderPath);
    if (!n.gShaderProgram)
    {
        fprintf(stderr, "error when reloading shader!\n");
    } else {
        glDeleteProgram(s->gShaderProgram);
        *s = n;
        printf("shader reload!\n");
    }
}

void sDeleteShaderProgram(ShaderProgram *s)
{
    glDeleteProgram(s->gShaderProgram);
}