#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include <glad/glad.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned int frameBufferObject;
    unsigned int frameBufferTexture;
    int width;
    int height;
} FrameBuffer;

FrameBuffer gCreateFrameBuffer(int width, int height);
void gDeleteFrameBuffer(FrameBuffer *b);

#endif