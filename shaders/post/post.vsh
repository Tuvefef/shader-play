#version 330 core

out vec2 gTexCoord;

#define _decode_bit2d(b) vec2(((b) << 1) & 2, (b) & 2)

void main()
{
    vec2 pos = _decode_bit2d(gl_VertexID);

    gTexCoord = pos;
    gl_Position = vec4(pos * 2.0 - 1.0, 0.0, 1.0);
}