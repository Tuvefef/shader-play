#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

//#define G_DEBUG

static inline const char *gErrStr(GLenum err)
{
    switch (err)
    {
        case GL_INVALID_ENUM: return "invalid enum";
        case GL_INVALID_VALUE: return "invalid value";
        case GL_INVALID_OPERATION: return "invalid operation";
        case GL_OUT_OF_MEMORY: return "out of memory";
        case GL_INVALID_FRAMEBUFFER_OPERATION: return "invalid framebuffer operation";
        default: return "unknown error";
    }
}

#define GLOG(fmt, ...)                                  \
    fprintf(stderr, "[LOG] " fmt "\n", ##__VA_ARGS__)

#define GWARN(fmt, ...)                                 \
    printf("[WARN] " fmt "\n", ##__VA_ARGS__)


#ifdef G_DEBUG
    #define GERR()                                                                                                  \
        do {                                                                                                        \
            GLenum err;                                                                                             \
            while ((err = glGetError()) != GL_NO_ERROR)                                                             \
            {                                                                                                       \
                fprintf(stderr, "[gl error] %s (0x%x) at %s:%d\n", gErrStr(err), err, __FILE__, __LINE__);          \
            }                                                                                                       \
        } while (0)

    #define VALID_GERR(x)           \
        do {                        \
            x;                      \
            GERR();                 \
        } while (0)

    #define GASSERT(c)                                                                          \
        do {                                                                                    \
            if (!(c))                                                                           \
            {                                                                                   \
                fprintf(stderr, "assert failed: %s\n archive: %s\n line: %d\n function: %s\n",  \
                    #c, __FILE__, __LINE__, __func__);                                          \
                abort();                                                                        \
            }                                                                                   \
        } while(0)
#else
    #define GERR() ((void)0)
    #define VALID_GERR(x) (x)
    #define GASSERT(c) ((void)0)
#endif

static inline void gCheckShaderCompile(unsigned int shader, const char *name)
{
    int success;
    char log[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1024, NULL, log);
        GLOG("[SHADER COMPILE ERROR] %s:\n%s\n", name, log);
    }
    else
    {
        fprintf(stderr, "[SHADER OK] %s compiled successfully\n", name);
    }
}

static inline void gCheckProgramLink(unsigned int program, const char *name)
{
    int success;
    char log[1024];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, log);
        GLOG("[PROGRAM LINK ERROR] %s:\n%s\n", name, log);
    }
    else
    {
        fprintf(stderr, "[PROGRAM OK] %s linked successfully\n", name);
    }
}

#define GCHECK_SHADER(shader, name) gCheckShaderCompile(shader, name)
#define GCHECK_PROGRAM(program, name) gCheckProgramLink(program, name)

#endif