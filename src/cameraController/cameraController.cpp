
#include "cameraController.h"
#include "camera/camera.h"
#include "input.h"
#include <glm/common.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/trigonometric.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

CameraController::CameraController(std::shared_ptr<Camera> camera)
    : camera(std::shared_ptr(camera)) {
  phi = glm::radians(180.0);
}

void CameraController::Tick() {
  CalculateAngles();
  CalculateCameraPosition();
}

void CameraController::CalculateCameraPosition() {
  float cam_x = cos(phi) * cos(theta);
  float cam_y = sin(theta);
  float cam_z = sin(phi) * cos(theta);

  camera->position = radius * glm::vec3(cam_x, cam_y, cam_z);
  glm::vec3 direction = glm::normalize(camera->position);
  camera->rotation = glm::quatLookAt(direction, glm::vec3(0.0, 1.0, 0.0));
}

void CameraController::CalculateAngles() {
  glm::vec2 cursor_pos = Input::GetCursorPosition();

  if (Input::IsMousePressed()) {
    glm::vec2 delta = cursor_pos - prev_cursor_pos;

    if (delta.length() <= 0) {
      return;
    }

    phi += cam_speed.y * delta.x;
    theta += cam_speed.x * delta.y;
  }
  int vertical_arrow_input = Input::GetVerticalArrowsValue();
  if (vertical_arrow_input != 0) {
    theta += vertical_arrow_input * cam_speed.y;
  }

  int horizontal_arrow_input = Input::GetHorizontalArrowsValue();
  if (horizontal_arrow_input != 0) {
    phi += horizontal_arrow_input * cam_speed.x;
  }

  prev_cursor_pos = cursor_pos;
}
