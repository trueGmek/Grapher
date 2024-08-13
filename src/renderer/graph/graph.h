#pragma once

#include "primitives/primitive.h"
#include <cstddef>
#include <glm/ext/vector_float4.hpp>

class Graph : public Primitive {
 public:
  std::size_t vertex_size{5};
  std::size_t points{10};
  std::size_t vertices_per_point{16};
  float distance_between_vertices{0.0};
  glm::vec4 color{constants::colors::white};

  std::vector<float> geometryBuffer{};

 public:
  Graph();
  void GenerateBuffer();
  void Draw(const glm::mat4& PV) override;

 private:
  void SetVBO(float* vertexData);
};
