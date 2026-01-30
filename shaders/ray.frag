#version 330 core

uniform vec2 gResolution;
uniform vec3 gColor;
uniform float gTime;

in vec2 gTexCoord;
out vec4 FragColor;

#define GTIME() (gTime * 1.2)

struct Ray
{
    vec3 gRayOrigin;
    vec3 gRayDirection;
};

float gRenderCube(vec3 gp, vec3 gsize)
{
    return length(max(abs(gp) - gsize, 0.0));
}

vec3 gMatrixRotateX(vec3 gp, float a)
{
    mat3 grot = mat3(
        vec3(cos(a), -sin(a), 0.0),
        vec3(sin(a), cos(a), 0.0),
        vec3(0.0, 0.0, 1.0)
    );

    return (grot * gp);
}

vec3 gMatrixRotateZ(vec3 gp, float a)
{
    mat3 grot = mat3(
        vec3(cos(a), 0.0, -sin(a)),
        vec3(0.0, 1.0, 0.0),
        vec3(sin(a), 0.0, cos(a))
    );

    return (grot * gp);
}

float gRenderCubeRotated(vec3 gp)
{
    gp = gMatrixRotateZ(gp, GTIME());
    gp = gMatrixRotateX(gp, GTIME());
    return gRenderCube(gp, vec3(0.45));
}

float gScene(vec3 gp)
{
    return gRenderCubeRotated(gp);
}

float gRayMarching(vec3 gro, vec3 grd, float start, float end)
{
    float gdepth = start;
    for (int i = 0; i < 255; i++)
    {
        vec3 gp = gro + gdepth * grd;
        float gd = gScene(gp);

        gdepth += gd;
        if (gd < 0.001 || gdepth > end)
            break;
    }

    return gdepth;
}

vec3 gCalculateNormal(vec3 gp)
{
    float eps = 0.001;
    float d = gRenderCubeRotated(gp);
    
    float dx = gRenderCubeRotated(gp + vec3(eps, 0.0, 0.0)) - d;
    float dy = gRenderCubeRotated(gp + vec3(0.0, eps, 0.0)) - d;
    float dz = gRenderCubeRotated(gp + vec3(0.0, 0.0, eps)) - d;
    
    return normalize(vec3(dx, dy, dz));
}

vec3 gBlinnPhong(vec3 normal, vec3 viewDir, vec3 lightDir, vec3 baseColor)
{
    float ambientStrength = 0.2;
    float diffuseStrength = 0.7;
    float specularStrength = 0.5;
    float shininess = 32.0;
    
    vec3 ambient = ambientStrength * baseColor;
    
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * diff * baseColor;
    
    vec3 halfVec = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfVec), 0.0), shininess);
    vec3 specular = specularStrength * spec * vec3(1.0);
    
    return ambient + diffuse + specular;
}

void main()
{
    vec2 uv = (gTexCoord - 0.5) * vec2(gResolution.x / gResolution.y, 1.0);

    Ray r;
    r.gRayOrigin = vec3(0.0, 0.0, 5.0);
    r.gRayDirection = normalize(vec3(uv, -1.0));

    vec3 rayOrigin = r.gRayOrigin;
    vec3 rayDirection = r.gRayDirection;

    float gd = gRayMarching(rayOrigin, rayDirection, 0.0, 100.0);

    vec3 gFinal = vec3(0.0);

    if (gd > 100.0)
    {
        gFinal = vec3(0.1);
    } else {
        vec3 hitPoint = rayOrigin + gd * rayDirection;
        vec3 normal = gCalculateNormal(hitPoint);
        
        vec3 lightDir = normalize(vec3(2.0, 2.0, 2.0));
        vec3 viewDir = -rayDirection;
        
        gFinal = gBlinnPhong(normal, viewDir, lightDir, gColor);
    }

    FragColor = vec4(gFinal, 1.0);
}