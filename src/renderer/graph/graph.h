
#pragma once

#include "primitives/primitive.h"
#include <cstddef>
#include <glm/ext/vector_float4.hpp>

class Graph : public Primitive {
public:
  std::size_t size{1};
  std::size_t points{10};
  std::size_t vertives{32};

  std::vector<float> buffer{};

public:
  Graph();
  void GenerateBuffer();
  void Draw(const glm::mat4 &PV) override;

private:
  void SetVBO(float *vertexData);
};
