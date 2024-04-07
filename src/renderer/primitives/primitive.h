#pragma once

#include "shader.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <vector>

#include "transform.h"

class Primitive : std::enable_shared_from_this<Primitive> {
public:
  Transform transform;

  std::vector<std::shared_ptr<Primitive>> children{};

  Primitive *parent;

protected:
  unsigned int VBO, VAO;

  Shader shader;

public:
  Primitive(auto vertexShaderPath, auto fragmentShaderPath)
      : shader(vertexShaderPath, fragmentShaderPath) {}

  virtual void Draw(const glm::mat4 &PV) = 0;

  void DrawRecursive(const glm::mat4 &PV) {

    Draw(PV);

    for (auto child : children) {
      child->DrawRecursive(PV * transform.CalculateTRS());
    }
  }

  void AddChild(const std::shared_ptr<Primitive> &child) {
    children.emplace_back(child);
    children.back()->parent = this;
  }

protected:
  /// This methods calculates and returns the Model-View-Projection matrix
  const glm::mat4 CalculateMVP(const glm::mat4 &PV) {

    return PV * transform.CalculateTRS();
  }
};
