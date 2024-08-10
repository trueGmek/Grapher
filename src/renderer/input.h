#pragma once

#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>

namespace Input {
inline GLFWwindow *window;

inline bool IsMousePressed() {
  return glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
}

inline glm::vec2 GetCursorPosition() {
  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);

  return glm::vec2{xpos, ypos};
}

inline int GetHorizontalArrowsValue() {

  int value{};
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
    value = 1;
  }

  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
    value = -1;
  }

  return value;
}

inline int GetVerticalArrowsValue() {

  int value{};
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
    value = 1;
  }

  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    value = -1;
  }

  return value;
}

} // namespace Input
//
