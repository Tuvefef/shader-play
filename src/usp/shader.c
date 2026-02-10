#include "../include/shaderplay/shader.h"
#include "../include/shaderplay/debug.h"
#include "../include/shaderplay/uniform.h"

#include <string.h>

static char *sReadShaderRecursive(const char *shaderPath, size_t *oSize)
{
    GASSERT(shaderPath != NULL);
    FILE *shaderFile = fopen(shaderPath, "rb");
    if (!shaderFile)
    {
        perror("fopen shader");
        return NULL;
    }

    char line[1024];
    size_t capst = 4096;
    size_t size = 0;
    char *buff = malloc(capst + 1);

    while (fgets(line, sizeof(line), shaderFile))
    {
        if (strncmp(line, "#include", 8) == 0)
        {
            char includeP[512];

            if (sscanf(line, "#include \"%[^\"]\"", includeP) == 1)
            {
                char dir[512];
                strcpy(dir, shaderPath);

                char *slash = strrchr(dir, '/');
                if (slash) *(slash + 1) = '\0';
                else dir[0] = '\0';

                char fullPath[1024];
                snprintf(fullPath, sizeof(fullPath), "%s%s", dir, includeP);

                size_t incsize = 0;
                char *incdata = sReadShaderRecursive(fullPath, &incsize);

                if (incdata)
                {
                    if (size + incsize + 1 >= capst)
                    {
                        capst = (size + incsize + 1) * 2;
                        char *tmp = realloc(buff, capst + 1);
                        if (!tmp) 
                        {
                            free(buff);
                            fclose(shaderFile);
                            return NULL;
                        }               
                        buff = tmp;
                    }

                    memcpy(buff + size, incdata, incsize);
                    size += incsize;

                    buff[size++] = '\n';

                    free(incdata);
                }
                continue;
            }
        }

        size_t len = strlen(line);

        if (size + len >= capst)
        {
            capst = (size + len) * 2;
            char *tmp = realloc(buff, capst);
            if(!tmp)
            {
                free(buff);
                fclose(shaderFile);
                return NULL;
            }
            buff = tmp;
        }

        memcpy(buff + size, line, len);
        size += len;
    }

    fclose(shaderFile);

    buff[size] = 0;

    if (oSize) *oSize = size;

    return buff;
    
}

static ShaderSource sReadShader(const char *shaderPath)
{
    GASSERT(shaderPath != NULL);
    ShaderSource src = {
        .shaderPath = shaderPath
    };

    src.shaderData = sReadShaderRecursive(shaderPath, &src.shaderSize);

    if (!(src.shaderData))
    {
        return VOIDSTRC(ShaderSource);
    }

    return src;
}

static void sDeleteShaderSource(ShaderSource *src)
{
    free(src->shaderData);
    src->shaderData = NULL;
    src->shaderSize = 0;
}

ShaderProgram sCreateShaderProgram(const char *vertexSource, const char *fragmentSource)
{
    ShaderProgram gShader = {
        .gShaderProgram = glCreateProgram(),
        .gVertexShaderPath = vertexSource,
        .gFragmentShaderPath = fragmentSource
    };

    unsigned int gVertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int gFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    gShader.gVertexShaderSource = sReadShader(vertexSource);
    gShader.gFragmentShaderSource = sReadShader(fragmentSource);

    glShaderSource(gVertexShader, 1, (const char**)&gShader.gVertexShaderSource.shaderData, NULL);
    glShaderSource(gFragmentShader, 1, (const char**)&gShader.gFragmentShaderSource.shaderData, NULL);

    glCompileShader(gVertexShader);
    glCompileShader(gFragmentShader);

    gCheckShaderCompile(gVertexShader, ":vertex:");
    GERR();

    gCheckShaderCompile(gFragmentShader, ":fragment:");
    GERR();

    glAttachShader(gShader.gShaderProgram, gVertexShader);
    glAttachShader(gShader.gShaderProgram, gFragmentShader);
    glLinkProgram(gShader.gShaderProgram);
    GCHECK_PROGRAM(gShader.gShaderProgram, "main");
    GERR();

    sDeleteShaderSource(&gShader.gVertexShaderSource);
    sDeleteShaderSource(&gShader.gFragmentShaderSource);

    glDeleteShader(gVertexShader);
    glDeleteShader(gFragmentShader);

    return gShader;
}

void gCacheUniforms(ShaderProgram *s)
{
    s->u.gColorLoc = gCreateUniform(s, "gColor");
    GERR();

    s->u.gResolutionLoc = gCreateUniform(s, "gResolution");
    GERR();

    s->u.gTimeLoc = gCreateUniform(s, "gTime");
    GERR();

    s->u.gMouse = gCreateUniform(s, "gMouse");
    GERR();

    s->u.gScene = gCreateUniform(s, "uScene");
}

void sReloadShaderProgram(ShaderProgram *s)
{
    GASSERT(s != NULL);
    if (!s || !s->gShaderProgram)
    {
        GLOG("invalid shader program pointer");
        return;
    }

    unsigned int oldProgram = s->gShaderProgram;
    ShaderProgram n = sCreateShaderProgram(s->gVertexShaderPath, s->gFragmentShaderPath);

    if (!n.gShaderProgram)
    {
        GLOG("error when reloading shader - keeping old program");
        return;
    }
    glDeleteProgram(oldProgram);
    *s = n;
    gCacheUniforms(s);

    printf("shader reload successful!\n");
}

void sDeleteShaderProgram(ShaderProgram *s)
{
    glDeleteProgram(s->gShaderProgram);
}