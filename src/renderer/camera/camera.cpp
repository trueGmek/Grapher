#include "camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <renderer.h>
#include "constants.h"

Camera::Camera() {}

glm::mat4 Camera::GetPVMatrix() {
  auto projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, NEAR, FAR);
  auto view = glm::lookAt(position, position + rotation * constants::vec3::forward, constants::vec3::up);

  return projection * view;
}
