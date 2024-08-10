#include "camera.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <renderer.h>

Camera::Camera() {}

glm::vec3 front = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 Camera::GetPVMatrix() {

  float aspect = Renderer::start_width / Renderer::start_height;

  auto projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, 0.1f, 10.0f);
  auto view = glm::lookAt(position, position + rotation * front, up);

  return projection * view;
}
