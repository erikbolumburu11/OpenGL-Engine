#pragma once

#include <linmath.h/linmath.h>
#include <Shader.hpp>
#include <Texture.hpp>

struct Material {
    Shader shader;
    Texture texture1;
    Texture texture2;
    vec4 color;

    Material(){};
};
