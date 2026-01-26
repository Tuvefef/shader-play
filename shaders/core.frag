#version 330 core

out vec4 FragColor;

#define SET_COLOR 1.0

vec3 gcolor()
{
    vec3 v00 = vec3(0.0, 1.0, 0.0);
    vec3 v11 = vec3(0.16, 0.45, 0.53);

    return mix(v00, v11, SET_COLOR);
}

void main()
{
    FragColor = vec4(gcolor(), 1.0);
}