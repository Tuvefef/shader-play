#ifndef SHADER_POINTER_H
#define SHADER_POINTER_H

#include "shader.h"

typedef struct 
{
    ShaderProgram *mainShader;
    ShaderProgram *postShader;
} ShaderPointers;

#endif