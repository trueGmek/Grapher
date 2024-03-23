#include "triangle.h"

const std::string VERTEX_SHADER_PATH = "../resources/shaders/triangle.vert";
const std::string FRAG_SHADER_PATH = "../resources/shaders/triangle.frag";

Triangle::Triangle() : Primitive(VERTEX_SHADER_PATH, FRAG_SHADER_PATH) {

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
}

void Triangle::Draw(const glm::mat4 &projection, const glm::mat4 &view) {

  shader.Use();
  shader.SetMat4Uniform(Shader::Keywords::MVP, CalculateMVP(projection, view));
  shader.SetVec4Uniform(Shader::Keywords::Color, color);

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  glBindVertexArray(0);
}
Triangle::~Triangle() {}
