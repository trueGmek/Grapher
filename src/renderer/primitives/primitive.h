#pragma once

#include "shader.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>

#include "glm/ext/quaternion_trigonometric.hpp"

class Primitive {
public:
  glm::vec3 position{0.0f, 0.0f, 0.0f};
  glm::vec3 scale{1, 1, 1};
  glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f};

protected:
  unsigned int VBO, VAO;

  Shader shader;

public:
  Primitive(auto vertexShaderPath, auto fragmentShaderPath)
      : shader(vertexShaderPath, fragmentShaderPath) {}

  virtual void Draw(const glm::mat4 &projection, const glm::mat4 &view) = 0;

protected:
  /// This methods calculates and returns the Model-View-Projection matrix
  const glm::mat4 CalculateMVP(const glm::mat4 &projection,
                               const glm::mat4 &view) {

    glm::mat4 model{1.0f};

    model = glm::translate(model, position);
    model = glm::rotate(model, angle(rotation), axis(rotation));
    model = glm::scale(model, scale);

    return projection * view * model;
  }
};
