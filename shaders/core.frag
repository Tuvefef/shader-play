#version 330 core

out vec4 FragColor;

#define OUT_COLOR
#ifdef OUT_COLOR
vec3 gcolor()
{
    return vec3(0.16, 0.45, 0.53);
}
#endif

void main()
{
    FragColor = vec4(gcolor(), 1.0);
}