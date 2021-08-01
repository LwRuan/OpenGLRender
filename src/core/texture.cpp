#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>

namespace ORTR{

bool Texture::loadTexture(const std::string &filename){
    name = filename;
    texData = stbi_load(filename.c_str(), &width, &height, NULL, 3);
    return (texData != nullptr);
}
};
