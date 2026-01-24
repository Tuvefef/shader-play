#ifndef SHADER_PLAY_H
#define SHADER_PLAY_H

#define GLERR()                                      \
    do {                                                \
        unsigned int err;                                     \
        while ((err = glGetError()) != GL_NO_ERROR)     \
            printf("[GL ERR] 0x%x\n", err);           \
    } while (0)

#include "window.h"
#include "shader.h"

#endif