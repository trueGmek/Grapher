#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/constants.hpp>
class Camera {
public:
  glm::vec3 position{glm::zero<glm::vec3>()};
  glm::quat rotation{glm::identity<glm::quat>()};
  float distance{3};

private:
public:
  glm::mat4 GetPVMatrix();

  void Tick();

  Camera();

private:
};
