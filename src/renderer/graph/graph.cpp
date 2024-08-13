#include "graph.h"

#include "constants.cpp"
#include "renderer.h"
#include "shader.h"
#include <GL/gl.h>
#include <GL/glext.h>
#include <glm/ext/vector_float2.hpp>
#include <vector>

const std::string VERTEX_SHADER_PATH{"../resources/shaders/emmit_sin.vert"};
const std::string GEOMETRY_SHADER_PATH{"../resources/shaders/emmit_sin.geom"};
const std::string FRAGMENT_SHADER_PATH{"../resources/shaders/emmit_sin.frag"};

Graph::Graph() : Primitive(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH, GEOMETRY_SHADER_PATH) {
  GenerateBuffer();
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * geometryBuffer.size(), geometryBuffer.data(),
               GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
};

void Graph::Draw(const glm::mat4 &PV) {
  shader.Use();

  glm::vec2 viewport = Renderer::GetViewportSize();

  shader.SetMat4Uniform(constants::shader::MVP, CalculateMVP(PV));
  shader.SetVec4Uniform(constants::shader::color, color);
  shader.SetVec2Uniform(constants::shader::viewport_size, viewport);

  shader.SetFloatUniform(constants::shader::vertices_per_point, vertices_per_point);
  shader.SetFloatUniform(constants::shader::distance_between_vertices, distance_between_vertices);
  shader.SetFloatUniform(constants::shader::point_pixel_size, vertex_size);

  glBindVertexArray(VAO);
  glDrawArrays(GL_POINTS, 0, points);

  glBindVertexArray(0);
}

void Graph::GenerateBuffer() {
  geometryBuffer.clear();
  float point_size_NDC = 2 * vertex_size / Renderer::viewport_width;
  float distance_between_points =
      (distance_between_vertices + point_size_NDC) * vertices_per_point + distance_between_vertices;

  for (int i = 0; i < points; i++) {
    geometryBuffer.push_back(0.0);
    geometryBuffer.push_back(0.0);
    geometryBuffer.push_back(distance_between_points * i);
  }

  geometryBuffer.shrink_to_fit();
}
