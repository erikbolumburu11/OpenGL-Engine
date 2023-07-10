#pragma once
#include <glm/glm.hpp>

namespace Components {
    namespace Lights{
        struct DirectionalLight {
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
        };
        
        struct PointLight {
            float constant;
            float linear;
            float quadratic;

            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
        };
    }
}