#pragma once

#include <vector>
#include <string>

namespace ORTR{

class Texture{
public:
    Texture() : texData(nullptr), width(0), height(0) {};
    ~Texture() { delete texData; }
    bool loadTexture(const std::string &filname);

    int width, height;
    unsigned char* texData;
    std::string name;
};
};