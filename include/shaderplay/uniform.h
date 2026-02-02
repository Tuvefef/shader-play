#ifndef UNIFORM_H
#define UNIFORM_H

#include <cgm/cgm.h>

typedef struct
{
    const char *uname;
    int uloc;
} Uniform;

typedef struct
{
    Uniform gColorLoc;
    Uniform gResolutionLoc;
    Uniform gTimeLoc;
    Uniform gMouse;
} ShaderUniform;

typedef struct ShaderProgram ShaderProgram;

Uniform gCreateUniform(ShaderProgram *s, const char *uname);

void gUniformVec3(Uniform *uptr, vec3 v);
void gUniformVec2(Uniform *uptr, vec2 v);
void gUniformFloat(Uniform *uptr, float f);

#endif