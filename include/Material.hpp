#pragma once

#include <glm/glm.hpp>
#include <Shader.hpp>
#include <Texture.hpp>

struct Material {
    Shader shader;
    Texture texture;
    glm::vec4 color;

    Material(){};
};
