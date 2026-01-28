#include "../include/shaderplay/uniform.h"
#include "../include/shaderplay/shader.h"
#include "../include/shaderplay/debug.h"

Uniform gCreateUniform(ShaderProgram *s, const char *uname)
{
    Uniform u = {
        .uname = uname
    };

    u.uloc = glGetUniformLocation(s->gShaderProgram, uname);
    GERR();
    return u;
}

void gUniformVec3(Uniform *uptr, vec3 v)
{
    if (uptr->uloc != -1)
    {
        glUniform3f(uptr->uloc, v.x, v.y, v.z);
        GERR();
    }
}

void gUniformVec2(Uniform *uptr, vec2 v)
{
    if (uptr->uloc != -1)
    {
        glUniform2f(uptr->uloc, v.x, v.y);
        GERR();
    }
}

void gUniformFloat(Uniform *uptr, float f)
{
    if (uptr->uloc != -1)
    {
        glUniform1f(uptr->uloc, f);
        GERR();
    }
}