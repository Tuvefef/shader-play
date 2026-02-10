#version 330 core

uniform sampler2D uScene;

in vec2 gTexCoord;
out vec4 FragColor;

void main()
{
    vec4 gFinal = texture(uScene, gTexCoord);
    //gFinal.rgb = 1.0 - gFinal.rgb;
    gFinal *= gFinal;

    FragColor = gFinal;
}