#pragma once

#include "primitives/primitive.h"
#include <glm/ext/vector_float4.hpp>
#include "constants.cpp"

class Graph : public Primitive {
 public:
  int vertex_size{5};
  int points{10};
  int vertices_per_point{16};

  float speed{1};
  float frequency{10};
  float amplitude{0.25};
  float distance_between_vertices{0.0};

  glm::vec4 color{constants::colors::white};

  std::vector<float> geometryBuffer{};

 public:
  Graph();
  void SetBuffers();
  void Draw(const glm::mat4& PV) override;

 private:
  void GenerateBuffer();
  void SetVBO();
};
