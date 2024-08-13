#pragma once

#include "../utils/constants.cpp"
#include "shader.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <vector>

#include "transform.h"

class Primitive {
public:
  Transform transform;
  Shader shader;

  Primitive *parent;
  std::vector<std::shared_ptr<Primitive>> children{};

protected:
  unsigned int VBO, VAO;

public:
  Primitive(auto vertexShaderPath, auto fragmentShaderPath)
      : shader(vertexShaderPath, fragmentShaderPath) {}

  Primitive(auto vertexShaderPath, auto fragmentShaderPath,
            auto geometryShaderPath)
      : shader(vertexShaderPath, fragmentShaderPath, geometryShaderPath) {}

  virtual void Draw(const glm::mat4 &PV) = 0;

  void DrawRecursive(const glm::mat4 &PV, float time) {

    shader.SetFloatUniform(constants::shader::time, time);
    Draw(PV);

    for (auto child : children) {
      child->DrawRecursive(PV * transform.CalculateTRS(), time);
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
