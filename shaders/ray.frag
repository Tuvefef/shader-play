#version 330 core

uniform vec2 gResolution;
uniform vec3 gColor;
uniform float gTime;

in vec2 gTexCoord;
out vec4 FragColor;

#define minx3(x, y, z) min(min(x, y), z)

struct Light
{
    vec3 lightPosition;
    vec3 lightDirection;
};

float gRenderSphere(vec3 p, vec3 c, float r)
{
    return length(p - c) - r;
}

float gRenderFloor(vec3 p, float h)
{
    return p.y - h;
}

float gScene(vec3 p)
{
    float sphere0 = gRenderSphere(p, vec3(0.0, 0.0, -2.0), 0.2);
    float sphere1 = gRenderSphere(p, vec3(1.0, 1.0, -4.0), 0.8);
    float floorf = gRenderFloor(p, -0.5);

    return minx3(sphere0, sphere1, floorf);
}

float gRayMarching(vec3 ro, vec3 rd, float start, float end)
{
    float depth = start;

    for (int i = 0; i < 200; i++)
    {
        vec3 p = ro + rd * depth;
        float d = gScene(p);

        if (d < 0.001 || depth > end)
            break;

        depth += d;
    }

    return depth;
}

vec3 gCalculateNormal(vec3 p)
{
    vec2 e = vec2(0.001, 0.0);

    return normalize(vec3(
        gScene(p + e.xyy) - gScene(p - e.xyy),
        gScene(p + e.yxy) - gScene(p - e.yxy),
        gScene(p + e.yyx) - gScene(p - e.yyx)
    ));
}

float gSoftShadow(vec3 ro, vec3 rd)
{
    float res = 1.0;
    float t = 0.02;

    for (int i = 0; i < 64; i++)
    {
        float h = gScene(ro + rd * t);
        res = min(res, 8.0 * h / t);
        t += clamp(h, 0.02, 0.1);
        if (h < 0.001) break;
    }

    return clamp(res, 0.0, 1.0);
}

float gAO(vec3 p, vec3 n)
{
    float ao = 0.0;
    float sca = 1.0;

    for (int i = 1; i <= 5; i++)
    {
        float h = 0.03 * float(i);
        float d = gScene(p + n * h);
        ao += (h - d) * sca;
        sca *= 0.7;
    }

    return clamp(1.0 - ao, 0.0, 1.0);
}

float gChecker(vec3 p)
{
    vec2 c = floor(p.xz);
    return mod(c.x + c.y, 2.0);
}

void main()
{
    vec2 uv = (gTexCoord - 0.5) * vec2(gResolution.x / gResolution.y, 1.0);

    vec3 ro = vec3(0.0, 0.0, 1.0);
    vec3 rd = normalize(vec3(uv, -1.0));

    vec3 finalColor = vec3(0.0);
    float d = gRayMarching(ro, rd, 0.1, 100.0);

    vec3 fogColor = vec3(0.62, 0.79, 0.87);

    if (d < 100.0)
    {
        vec3 p = ro + rd * d;
        vec3 n = gCalculateNormal(p);

        Light gl;

        gl.lightPosition = vec3(2.0, 2.0, 4.0);
        vec3 lightPos = gl.lightPosition;

        gl.lightDirection = normalize(lightPos - p);
        vec3 lightDir = gl.lightDirection;

        vec3 viewDir  = normalize(ro - p);
        vec3 halfDir  = normalize(lightDir + viewDir);

        float diff = max(dot(n, lightDir), 0.0);
        float spec = pow(max(dot(n, halfDir), 0.0), 32.0);

        float shadow = gSoftShadow(p + n * 0.01, lightDir);
        float ao = gAO(p, n);

        vec3 color = gColor * diff + vec3(1.0) * spec * 0.4;
        color += vec3(0.15);

        if (abs(gRenderFloor(p, -0.5)) < 0.001)
        {
            float c = gChecker(p);
            color *= mix(0.7, 1.3, c);
        }

        color *= shadow;
        color *= ao;

        float fog = exp(-d * 0.04);
        finalColor = mix(fogColor, color, fog);
    }
    else
    {
        finalColor = fogColor;
    }

    FragColor = vec4(finalColor, 1.0);
}
