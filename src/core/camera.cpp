#include "camera.h"

#include <cstring>

namespace ORTR{

Camera::Camera(vec3 eye, vec3 lookat, float _fov){
    position = eye;
    pivot = lookat;
    worldUp = vec3(0, 1, 0);

    vec3 dir = normalize(pivot - position);
    pitch = degrees(asin(dir.y));
    yaw = degrees(atan2(dir.z, dir.x));

    radius = distance(eye, lookat);
    fov = _fov;
    focalDist = 0.1f;
    aperture = 0.0;
    updateCamera();
}

Camera::Camera(const Camera& other){
    *this = other;
}

Camera& Camera::operator = (const Camera& other){
    ptrdiff_t l = (unsigned char*)&isMoving - (unsigned char*)&position.x;
    isMoving = memcmp(&position.x, &other.position.x, l) != 0;
    memcpy(&position.x, &other.position.x, l);
    return *this;
}

void Camera::updateCamera(){
    vec3 forward_temp;
    forward_temp.x = cos(radians(yaw)) * cos(radians(pitch));
    forward_temp.y = sin(radians(pitch));
    forward_temp.z = sin(radians(yaw)) * cos(radians(pitch));

    forward = normalize(forward_temp);
    position = pivot + (forward * -1.0f) * radius;

    right = normalize(cross(forward, worldUp));
    up = normalize(cross(right, forward));
}

};