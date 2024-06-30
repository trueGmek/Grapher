#pragma once

#include "primitives/primitive.h"
#include <glm/ext/vector_float4.hpp>

class Point : public Primitive {
public:
  Point();

  void Draw(const glm::mat4 &PV) override;

  glm::vec4 color;
  std::size_t size{1};

private:
  const float vertices[3] = {
      0.0f, 0.0f, 0.0f //
  };
};
