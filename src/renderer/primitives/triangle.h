#pragma once

#include <glm/ext/vector_float3.hpp>
#include <primitives/primitive.h>

class Triangle : public Primitive {
public:
  Triangle();
  ~Triangle();

  glm::vec4 color{};

  void Draw(const glm::mat4 &projection, const glm::mat4 &view) override;

private:
  const float vertices[9] = {
      -0.5f, -0.5f, 0.0f, //
      0.5f,  -0.5f, 0.0f, //
      0.0f,  0.5f,  0.0f  //
  };
};
