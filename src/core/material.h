#pragma once

#include "glm.hpp"
#include <vector>

using namespace glm;

namespace ORTR{

class Material{
public:
    Material()
    {
        albedo   = vec3(1.0f, 1.0f, 1.0f);
        specular = 0.5f;

        emission    = vec3(0.0f, 0.0f, 0.0f);
        anisotropic = 0.0f;

        metallic     = 0.0f;
        roughness    = 0.5f;
        subsurface   = 0.0f;
        specularTint = 0.0f;
        
        sheen          = 0.0f;
        sheenTint      = 0.0f;
        clearcoat      = 0.0f;
        clearcoatGloss = 0.0f;

        transmission = 0.0f;
        ior          = 1.45f;
        atDistance   = 1.0f;
        padding1     = 0.0f;

        extinction    = vec3(1.0f, 1.0f, 1.0f);
        padding2      = 0.0f;

        albedoTexID            = -1.0f;
        metallicRoughnessTexID = -1.0f;
        normalmapTexID         = -1.0f;
        padding3               =  0.0f;
    };

    vec3 albedo;
    float specular;

    vec3 emission;
    float anisotropic;

    float metallic;
    float roughness;
    float subsurface;
    float specularTint;

    float sheen;
    float sheenTint;
    float clearcoat;
    float clearcoatGloss;

    float transmission;
    float ior;
    float atDistance;
    float padding1;

    vec3 extinction;
    float padding2;

    float albedoTexID;
    float metallicRoughnessTexID;
    float normalmapTexID;
    float padding3;
};
};