#pragma once

#include <glm.hpp>
using namespace glm;

namespace ORTR
{

struct RenderOptions
{
    RenderOptions(){
        resolution = ivec2(1280, 720);
    }
    ivec2 resolution;
};


};