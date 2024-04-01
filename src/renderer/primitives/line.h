
#pragma once

#include "primitives/primitive.h"
#include <glm/ext/vector_float4.hpp>

class Line : public Primitive {
public:
  Line(glm::vec3 start, glm::vec3 end);

  void Draw(const glm::mat4 &projection, const glm::mat4 &view) override;
  glm::vec4 color;

private:
  const float vertices[6];
};
