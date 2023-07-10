#pragma once

#include <glm/glm.hpp>
#include <Shader.hpp>
#include <Texture.hpp>

struct Material {
    Shader shader;
    Texture diffuse;
    Texture specular;
    float shininess = 64.0f;

    Material(){};
};
