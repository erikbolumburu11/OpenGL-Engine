#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Game.hpp>
#include <Components/Shape.hpp>

void Components::Shape::Initialize(std::vector<float> vertices, glm::vec3 pos, Material mat) {

    unsigned int VBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);  

    worldPosition = pos;

    material = mat;

    model = glm::mat4(1.0f);

    projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    material.shader.setMat4("model", model);
    material.shader.setMat4("projection", projection);
}

void Components::OnShapeConstructed(Components::ShapeData sd, entt::registry& reg, entt::entity e) {
	Components::Shape& shape = reg.get<Components::Shape>(e);
    shape.Initialize(sd.vertices, sd.pos, sd.mat);
}