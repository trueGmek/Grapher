#include "point.h"

#include <GL/gl.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

const std::string VERTEX_SHADER_PATH{"../resources/shaders/point.vert"};
const std::string FRAGMENT_SHADER_PATH{"../resources/shaders/point.frag"};
const std::string GEOMETRY_SHADER_PATH{"../resources/shaders/emmit_sin.geom"};


Point::Point()
    : Primitive(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH,
                GEOMETRY_SHADER_PATH) {

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

void Point::Draw(const glm::mat4 &PV) {

  shader.Use();
  shader.SetMat4Uniform(Shader::Keywords::MVP, CalculateMVP(PV));
  shader.SetVec4Uniform(Shader::Keywords::Color, color);
  glBindVertexArray(VAO);

  glPointSize(size);
  glDrawArrays(GL_POINTS, 0, 1);

  glBindVertexArray(0);
}
