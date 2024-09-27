#pragma once

#include <imgui.h>
#include "renderer.h"
#include <glm/ext/vector_float2.hpp>

namespace Input {

inline bool IsMousePressed() {
  return glfwGetMouseButton(Renderer::window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS &&
         ImGui::IsAnyItemHovered() == false;
}

inline glm::vec2 GetCursorPosition() {
  double xpos, ypos;
  glfwGetCursorPos(Renderer::window, &xpos, &ypos);

  return glm::vec2{xpos, ypos};
}

inline int GetHorizontalArrowsValue() {
  int value{};
  if (glfwGetKey(Renderer::window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    value = 1;
  }

  if (glfwGetKey(Renderer::window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    value = -1;
  }

  return value;
}

inline int GetVerticalArrowsValue() {
  int value{};
  if (glfwGetKey(Renderer::window, GLFW_KEY_UP) == GLFW_PRESS) {
    value = 1;
  }

  if (glfwGetKey(Renderer::window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    value = -1;
  }

  return value;
}

}  // namespace Input
//
