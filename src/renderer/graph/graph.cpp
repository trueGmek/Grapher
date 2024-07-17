#include "graph.h"

#include "constants.cpp"
#include <vector>

const std::string VERTEX_SHADER_PATH{"../resources/shaders/emmit_sin.vert"};
const std::string GEOMETRY_SHADER_PATH{"../resources/shaders/emmit_sin.geom"};
const std::string FRAGMENT_SHADER_PATH{"../resources/shaders/emmit_sin.frag"};

Graph::Graph()
    : Primitive(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH,
                GEOMETRY_SHADER_PATH) {

  GenerateBuffer();
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer.size(), buffer.data(),
               GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
};

void Graph::Draw(const glm::mat4 &PV) {

  shader.Use();
  shader.SetMat4Uniform(constants::shader::MVP, CalculateMVP(PV));
  glBindVertexArray(VAO);

  glPointSize(size);
  glDrawArrays(GL_POINTS, 0, points);

  glBindVertexArray(0);
}

void Graph::GenerateBuffer() {
  buffer.clear();

  for (int i = 0; i < points; i++) {
    buffer.push_back(0.32 * i);
    buffer.push_back(0);
    buffer.push_back(0);
  }

  buffer.shrink_to_fit();
}
