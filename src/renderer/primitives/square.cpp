#include "square.h"
#include "primitives/primitive.h"

#include "glm/ext/quaternion_trigonometric.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

const std::string VERTEX_SHADER_PATH = "../resources/shaders/triangle.vert";
const std::string FRAG_SHADER_PATH = "../resources/shaders/triangle.frag";

Square::Square() : Primitive(VERTEX_SHADER_PATH, FRAG_SHADER_PATH) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
}

void Square::Draw(const glm::mat4 &projection, const glm::mat4 &view) {

  glm::mat4 model{1.0f};

  model = glm::translate(model, Position);
  model = glm::rotate(model, angle(Rotation), axis(Rotation));
  model = glm::scale(model, Scale);

  glm::mat4 mvp = projection * view * model;

  shader.Use();
  shader.SetMat4Uniform("MVP", mvp);
  shader.SetVec4Uniform("uColor", color);
  glBindVertexArray(VAO);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

  glBindVertexArray(0);
}

Square::~Square() {}
