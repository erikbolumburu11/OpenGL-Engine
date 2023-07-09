#include <entt/entity/registry.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <constants.hpp>
#include "Components/Camera.hpp"
#include "Components/Transform.hpp"

void Components::Camera::CameraUpdate(GLFWwindow* window, Components::Camera::Camera* activeCam, entt::registry& reg, float deltaTime)
{
    auto cams = reg.view<Components::Camera::Camera>();

    glm::vec2 mouseOffset = Components::Camera::GetMouseOffset(window);

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if(state == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        cams.each([&](Components::Camera::Camera& cam){
            Components::Camera::Move(&cam, activeCam, window, reg, deltaTime);
            Components::Camera::Look(&cam, activeCam, mouseOffset);
        });
    }
    else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}

void Components::Camera::UpdateCameraVectors(Components::Camera::Camera* cam)
{
    glm::vec3 _front;
    _front.x = cos(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
    _front.y = sin(glm::radians(cam->pitch));
    _front.z = sin(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
    cam->front = glm::normalize(_front);

    cam->right = glm::normalize(glm::cross(cam->front, cam->worldUp));  
    cam->up = glm::normalize(glm::cross(cam->right, cam->front));
}

glm::mat4 Components::Camera::GetViewMatrix(Components::Camera::Camera *cam, entt::registry& reg) {
    entt::entity camEntity = entt::to_entity(reg, *cam);
    glm::vec3& pos = reg.get<Components::Transform>(camEntity).pos;
    return glm::lookAt(pos, pos + cam->front, cam->up);
}

void Components::Camera::Move(Components::Camera::Camera* cam, Components::Camera::Camera* activeCam, GLFWwindow *window, entt::registry& reg, float deltaTime)
{
    if(cam == activeCam){
        entt::entity camEntity = entt::to_entity(reg, *cam);
        glm::vec3& pos = reg.get<Components::Transform>(camEntity).pos;
        float vel = cam->moveSpeed * deltaTime;
        if(glfwGetKey(window, GLFW_KEY_W)) pos += cam->front * vel;
        if(glfwGetKey(window, GLFW_KEY_S)) pos -= cam->front * vel;
        if(glfwGetKey(window, GLFW_KEY_A)) pos -= cam->right * vel;
        if(glfwGetKey(window, GLFW_KEY_D)) pos += cam->right * vel;
    }
}

glm::vec2 Components::Camera::GetMouseOffset(GLFWwindow *window)
{
    static bool firstMouse = true;

    static double lastMousePosX = SCREEN_WIDTH / 2;
    static double lastMousePosY = SCREEN_HEIGHT / 2;
    double mousePosX = SCREEN_WIDTH / 2;
    double mousePosY = SCREEN_HEIGHT / 2;

    if (firstMouse)
    {
        lastMousePosX = mousePosX;
        lastMousePosY = mousePosY;
        firstMouse = false;
    }

    glfwGetCursorPos(window, &mousePosX, &mousePosY);

    float xOffset = mousePosX - lastMousePosX;
    float yOffset = lastMousePosY - mousePosY;

    lastMousePosX = mousePosX;
    lastMousePosY = mousePosY;

    return glm::vec2(xOffset, yOffset);
}

void Components::Camera::Look(Components::Camera::Camera *cam, Components::Camera::Camera *activeCam, glm::vec2 mouseOffset)
{
    if(cam == activeCam){
        // Rotate Camera
        mouseOffset *= cam->mouseSensitivity;

        cam->yaw += mouseOffset.x;
        cam->pitch += mouseOffset.y;

        if (cam->pitch > 89.0f) cam->pitch = 89.0f;
        if (cam->pitch < -89.0f) cam->pitch = -89.0f;

        Components::Camera::UpdateCameraVectors(cam);
    }
}