#pragma once

#include "glm.hpp"
using namespace glm;

namespace ORTR{

class Camera
{
public:
    Camera(vec3 eye, vec3 lookat, float fov);
    Camera(const Camera& other);
    Camera& operator = (const Camera& other);

    // Variables
    vec3 position;
    vec3 up;
    vec3 right;
    vec3 forward;

    vec3 worldUp;
    vec3 pivot;

    float focalDist;
    float aperture;
    float fov;
    float pitch;
    float radius;
    float yaw;
    bool isMoving;

    // Functions
    void updateCamera();
};

};
