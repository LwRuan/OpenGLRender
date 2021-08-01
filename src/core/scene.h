#pragma once

#include "camera.h"
#include "renderer.h"

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

    
};
};