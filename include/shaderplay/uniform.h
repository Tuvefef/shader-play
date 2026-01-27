#ifndef UNIFORM_H
#define UNIFORM_H

#include <cgm/cgm.h>
#include "shader.h"

typedef struct
{
    const char *uname;
    int uloc;
} Uniform;

/**
 * @brief create the uniform location
 * @return Uniform 
 * @note It only has to be called after calling the program inside the loop
 */
Uniform gCreateUniform(ShaderProgram s, const char *uname);

void gUniformVec3(Uniform *uptr, vec3 v);

#endif