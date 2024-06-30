
#include "line.h"
#include "constants.cpp"

#include <GL/gl.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

const std::string VERTEX_SHADER_PATH{"../resources/shaders/point.vert"};
const std::string FRAGMENT_SHADER_PATH{"../resources/shaders/point.frag"};

Line::Line(glm::vec3 start, glm::vec3 end)
    : Primitive(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH),
      vertices{start.x, start.y, start.z, end.x, end.y, end.z} {

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

void Line::Draw(const glm::mat4 &PV) {
  shader.Use();
  shader.SetMat4Uniform(constants::shader::MVP, CalculateMVP(PV));
  shader.SetVec4Uniform(constants::shader::color, color);
  glBindVertexArray(VAO);

  glDrawArrays(GL_LINES, 0, 2);

  glBindVertexArray(0);
}
