#pragma once

#include "glm.hpp"

#include <vector>
#include <string>

using namespace glm;

namespace ORTR{

class Mesh{
public:
    Mesh(){};
    ~Mesh(){};

    std::vector<vec4> verticesUVX;
    std::vector<vec4> normalsUVY;

    std::string name;

    bool loadFromFile(const std::string& filename);
};

class MeshInstance{
public:
    MeshInstance(std::string name, mat4 xform, int matId, int meshId)
        : name(name)
        , meshID(meshId)
        , transform(xform) 
        , materialID(matId) 
    {}
    ~MeshInstance() {}

    mat4 transform;
    std::string name;

    int materialID;
    int meshID;
};
};