#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include "uniform.h"

#define VOIDSTRC(x) ((x){0})

typedef struct
{
    char *shaderData;
    size_t shaderSize;
    const char *shaderPath;
} ShaderSource;

struct ShaderProgram
{
    unsigned int gShaderProgram;
    ShaderSource gVertexShaderSource;
    ShaderSource gFragmentShaderSource;

    ShaderUniform u;

    const char *gVertexShaderPath;
    const char *gFragmentShaderPath;
};

ShaderProgram sCreateShaderProgram(const char *vertexSource, const char *fragmentsource);

void gCacheUniforms(ShaderProgram *s);
void sReloadShaderProgram(ShaderProgram *s);
void sDeleteShaderProgram(ShaderProgram *s);

#endif