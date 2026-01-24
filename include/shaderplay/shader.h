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
} ShaderProgram;

ShaderProgram sCreateShaderProgram(const char *vertexSource, const char *fragmentsource);
void sDeleteShaderProgram(ShaderProgram *gs);

#endif