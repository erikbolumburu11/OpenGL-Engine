#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Game.hpp>
#include <Shape.hpp>

void Shape::Initialize(std::vector<float> vertices, glm::vec3 pos, Material mat) {

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

    material = mat;
    view = glm::mat4(1.0f);
    model = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);

    worldPosition = pos;

    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    material.shader.setMat4("model", model);
    material.shader.setMat4("view", view);
    material.shader.setMat4("projection", projection);
}

void OnShapeConstructed(ShapeData sd, entt::registry& reg, entt::entity e) {
	Shape& shape = reg.get<Shape>(e);
    shape.Initialize(sd.vertices, sd.pos, sd.mat);
}