#version 330 core

uniform vec2 gResolution;
uniform vec3 gColor;
uniform float gTime;

in vec2 gTexCoord;
out vec4 FragColor;

void main()
{
    vec2 uv = gTexCoord * 2.0 - 1.0;
    uv.x *= gResolution.x / gResolution.y;

    float wave = sin(uv.x * 4.0 + gTime) * 0.1;
    uv.y += wave;

    float t = 0.5 + 0.5 * sin(gTime + length(uv) * 4.0);
    vec3 col = mix(gColor, vec3(uv * 0.5 + 0.5, 0.5), t);

    FragColor = vec4(col, 1.0);
}