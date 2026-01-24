#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

#define GLERR()                                      \
    do {                                                \
        unsigned int err;                                     \
        while ((err = glGetError()) != GL_NO_ERROR)     \
            printf("[GL ERR] 0x%x\n", err);           \
    } while (0)

typedef struct
{
    unsigned int gShaderProgram;
} ShaderProgram;

ShaderProgram sCreateShaderProgram(const char *vertexSource, const char *fragmentsource);
void sDeleteShaderProgram(ShaderProgram *gs);

#endif