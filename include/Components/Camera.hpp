#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <entt/entt.hpp>

namespace Components {
    namespace Camera {

        struct Camera {
            public:
            glm::vec3 pos = glm::vec3(0, 0, 0);
            glm::vec3 front = glm::vec3(0, 0, -1);
            glm::vec3 up = glm::vec3(0, 1, 0);
            glm::vec3 right;
            glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

            float yaw = -90.0f;
            float pitch = 0.0f;

            float moveSpeed = 2.5f;
            float mouseSensitivity = 0.1f;
            float fov = 45;
        };

        void CameraUpdate(GLFWwindow* window, Components::Camera::Camera* activeCam, entt::registry& reg, float deltaTime);
        
        void UpdateCameraVectors(Components::Camera::Camera* cam);

        glm::mat4 GetViewMatrix(Components::Camera::Camera* cam);

        void Move(Components::Camera::Camera* cam, Components::Camera::Camera* activeCam, GLFWwindow* window, float deltaTime);
        void Look(Components::Camera::Camera* cam, Components::Camera::Camera* activeCam, GLFWwindow* window, float deltaTime);
    }
}