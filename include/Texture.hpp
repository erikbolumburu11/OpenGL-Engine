#pragma once
#include <string>
#include <stb_image.h>

struct Texture {
    unsigned int ID;

    Texture(){};
    Texture(std::string filePath);
};