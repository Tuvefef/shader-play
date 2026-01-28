#include "../include/shaderplay/shader.h"
#include "../include/shaderplay/debug.h"
#include "../include/shaderplay/uniform.h"

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

static void sDeleteShaderSource(ShaderSource *src)
{
    free(src->shaderData);
    src->shaderData = NULL;
    src->shaderSize = 0;
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

    gCheckShaderCompile(gVertexShader, ":vertex:");
    GERR();

    gCheckShaderCompile(gFragmentShader, ":fragment:");
    GERR();

    glAttachShader(gShader.gShaderProgram, gVertexShader);
    glAttachShader(gShader.gShaderProgram, gFragmentShader);
    glLinkProgram(gShader.gShaderProgram);
    GCHECK_PROGRAM(gShader.gShaderProgram, "main");
    GERR();

    sDeleteShaderSource(&gShader.gVertexShaderSource);
    sDeleteShaderSource(&gShader.gFragmentShaderSource);

    glDeleteShader(gVertexShader);
    glDeleteShader(gFragmentShader);

    return gShader;
}

void gCacheUniforms(ShaderProgram *s)
{
    s->u.gColorLoc = gCreateUniform(s, "gColor");
    GERR();

    s->u.gResolutionLoc = gCreateUniform(s, "gResolution");
    GERR();

    s->u.gTimeLoc = gCreateUniform(s, "gTime");
    GERR();
}

void sReloadShaderProgram(ShaderProgram *s)
{
    if (!s || !s->gShaderProgram)
    {
        GLOG("invalid shader program pointer");
        return;
    }

    unsigned int oldProgram = s->gShaderProgram;
    ShaderProgram n = sCreateShaderProgram(s->gVertexShaderPath, s->gFragmentShaderPath);

    if (!n.gShaderProgram)
    {
        GLOG("error when reloading shader - keeping old program");
        return;
    }
    glDeleteProgram(oldProgram);
    *s = n;
    gCacheUniforms(s);

    printf("shader reload successful!\n");
}

void sDeleteShaderProgram(ShaderProgram *s)
{
    glDeleteProgram(s->gShaderProgram);
}