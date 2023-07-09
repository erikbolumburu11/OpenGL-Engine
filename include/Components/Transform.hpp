#pragma once
#include <glm/glm.hpp>

namespace Components {
    struct Transform {
        glm::vec3 pos = glm::vec3(1);
        glm::vec3 rot = glm::vec3(1);
        glm::vec3 scale = glm::vec3(1);
    };
}