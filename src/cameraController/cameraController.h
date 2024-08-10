#pragma once

#include "camera/camera.h"
#include <glm/ext/vector_float2.hpp>
#include <memory>

class CameraController {
private:
  std::shared_ptr<Camera> camera;
  float phi{};
  float theta{};
  float radius = 3;

  glm::vec2 prev_cursor_pos;
  glm::vec2 cam_speed{0.01, 0.01};

public:
  CameraController(std::shared_ptr<Camera> camera);
  void Tick();

private:
  void CalculateCameraPosition();
  void CalculateAngles();
};
