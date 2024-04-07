#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <primitives/primitive.h>

class Triangle : public Primitive {
public:
  Triangle();

  glm::vec4 color{};

  void Draw(const glm::mat4 &PV) override;

private:
  const float vertices[9] = {
      -0.5f, -0.5f, 0.0f, //
      0.5f,  -0.5f, 0.0f, //
      0.0f,  0.5f,  0.0f  //
  };
};
