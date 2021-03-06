#pragma once

#include "camera.h"
#include "renderer.h"
#include "mesh.h"
#include "material.h"
#include "texture.h"

#include <vector>

namespace ORTR{

class Camera;

enum LightType{
    RectLight,
    SphereLight,
    DistantLight
};

struct Light{
    vec3 position;
    vec3 emission;
    vec3 u;
    vec3 v;
    float radius;
    float area;
    float type;
};

struct Indices{
    int x, y, z;
};

class Scene{
public:

    RenderOptions renderOptions;

    std::vector<Mesh> meshes;

    std::vector<Indices> vertIndices;
    std::vector<vec4> verticesUVX;
    std::vector<vec4> normalsUVY;
    std::vector<mat4> transforms;

    std::vector<Material> materials;
    std::vector<MeshInstance> MeshInstance;
    bool instancesModified = false;

    std::vector<Light> lights;

    Camera* camera;

    std::vector<Texture*> textures;
    std::vector<unsigned char> textureMapsArray;
};
};