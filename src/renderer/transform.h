#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>

struct Transform {
  glm::vec3 position{0.0, 0.0, 0.0};
  glm::vec3 scale{1, 1, 1};
  glm::quat rotation{glm::vec3{0.0, 0.0, 0.0}};
  glm::mat4 model{1.0};
};
