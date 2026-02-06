float gRenderCube(vec3 gp, vec2 mouse)
{
    return length(max(abs(gp) - vec3(0.9) + mouse.x, 0.0));
}