#include "graph.h"

#include "constants.cpp"

const std::string VERTEX_SHADER_PATH{"../resources/shaders/point.vert"};
const std::string FRAGMENT_SHADER_PATH{"../resources/shaders/point.frag"};
const std::string GEOMETRY_SHADER_PATH{"../resources/shaders/emmit_sin.geom"};

Graph::Graph()
    : Primitive(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH, GEOMETRY_SHADER_PATH) {

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
};

void Graph::Draw(const glm::mat4 &PV) {

  shader.Use();
  shader.SetMat4Uniform(constants::shader::MVP, CalculateMVP(PV));
  shader.SetVec4Uniform(constants::shader::color, color);
  glBindVertexArray(VAO);

  glPointSize(size);
  glDrawArrays(GL_POINTS, 0, 1);

  glBindVertexArray(0);
}
