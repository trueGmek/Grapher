#pragma once
#include "GUI/GUI.h"
#include "primitives/line.h"
#include "primitives/point.h"
#include "primitives/square.h"
#include "primitives/triangle.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>

class Renderer {
public:
  Renderer(){};

  bool Initialize();
  void Update();
  void Finalize();

  bool IsClosing() { return glfwWindowShouldClose(window); }

  glm::mat4 view{1.0f};
  glm::mat4 projection{1.0f};

  constexpr static const float start_width = 1600;
  constexpr static const float start_height = 1200;

private:
  GUI ui;
  unsigned int VBO, VAO;

  GLFWwindow *window = nullptr;

  void ProcessEvents();
  bool CreateWindow();
  void RenderPrimitives();

  std::unique_ptr<Triangle> triangle;
  std::unique_ptr<Square> square;
  std::unique_ptr<Point> point;
  std::unique_ptr<Line> x_line,y_line,z_line;
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);