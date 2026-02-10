#include "../include/shaderplay/buffer.h"
#include "../include/shaderplay/debug.h"

FrameBuffer gCreateFrameBuffer(int width, int height)
{
    FrameBuffer b = {
        .width = width,
        .height = height
    };

    glGenFramebuffers(1, &b.frameBufferObject);
    glBindFramebuffer(GL_FRAMEBUFFER, b.frameBufferObject);

    glGenTextures(1, &b.frameBufferTexture);
    glBindTexture(GL_TEXTURE_2D, b.frameBufferTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, b.frameBufferTexture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        GLOG("incomplete framebuffer\n");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return b;
}

void gDeleteFrameBuffer(FrameBuffer *b)
{
    glDeleteFramebuffers(1, &b->frameBufferObject);
}