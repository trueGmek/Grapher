#pragma once

#include "primitive.h"
#include <glm/ext/vector_float3.hpp>

class Square : public Primitive {
public:
  glm::vec4 color;

private:
  unsigned int EBO;
  const float vertices[12] = {
      0.5f,  0.5f,  0.0f, // top right
      0.5f,  -0.5f, 0.0f, // bottom right
      -0.5f, -0.5f, 0.0f, // bottom left
      -0.5f, 0.5f,  0.0f  // top left
  };

  const unsigned int indices[6] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };
  // const float vertices[12]{
  //     -0.5, 0.5,  0.0, // TOP LEFT
  //     0.5,  0.5,  0.0, // TOP RIGHT
  //     -0.5, -0.5, 0.0, // BOTTOM LEFT
  //     0.5,  -0.5, 0.0, // BOTTOM RIGHT
  // };
  //
  // const float indicies[6]{0, 2, 3,  //
  //                         0, 1, 3}; //
public:
  Square();
  ~Square();

  void Draw(const glm::mat4 &projection, const glm::mat4 &view) override;
};
