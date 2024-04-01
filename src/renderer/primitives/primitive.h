#pragma once

#include "shader.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>
#include <memory>
#include <vector>

#include "glm/ext/quaternion_trigonometric.hpp"
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

  virtual void Draw(const glm::mat4 &projection, const glm::mat4 &view) = 0;

  template <typename T> void AddChild(const std::shared_ptr<T> &child) {

    children.emplace_back(std::shared_ptr(child));
    children.back()->parent = this;
  }

  template <typename T> void AddChild(std::unique_ptr<T> &&child) {

    children.emplace_back(std::shared_ptr<T>(std::move(child)));
    children.back()->parent = this;
  }

protected:
  /// This methods calculates and returns the Model-View-Projection matrix
  const glm::mat4 CalculateMVP(const glm::mat4 &projection,
                               const glm::mat4 &view) {

    glm::mat4 TRS{1.0f};

    TRS = glm::translate(TRS, transform.position);
    TRS = glm::rotate(TRS, angle(transform.rotation), axis(transform.rotation));
    TRS = glm::scale(TRS, transform.scale);

    if (parent == nullptr) {
      return projection * view * TRS;
    }

    return parent->CalculateMVP(projection, view) * projection * view * TRS;
  }
};
