#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

#define VOIDSTRC(x) ((x){0})

typedef struct
{
    char *shaderData;
    size_t shaderSize;
    const char *shaderPath;
} ShaderSource;

typedef struct
{
    unsigned int gShaderProgram;
    ShaderSource gVertexShaderSource;
    ShaderSource gFragmentShaderSource;

    const char *gVertexShaderPath;
    const char *gFragmentShaderPath;
} ShaderProgram;

ShaderProgram sCreateShaderProgram(const char *vertexSource, const char *fragmentsource);

void sReloadShaderProgram(ShaderProgram *s);
void sDeleteShaderProgram(ShaderProgram *s);

#endif