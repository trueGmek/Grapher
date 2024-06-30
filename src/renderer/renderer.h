#pragma once
#include "GUI/GUI.h"
#include "primitives/primitive.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <memory>

class Renderer {
public:
  bool Initialize();
  void Update();
  void Finalize();

  bool IsClosing() { return glfwWindowShouldClose(window); }

  glm::mat4 view{1.0f};
  glm::mat4 projection{1.0f};

  bool drawWireFrame = false;

  constexpr static const float start_width = 1600;
  constexpr static const float start_height = 1200;

private:
  GUI ui;
  unsigned int VBO, VAO;

  GLFWwindow *window = nullptr;

  void ProcessEvents();
  bool CreateWindow();
  void RenderScene(const std::shared_ptr<Primitive> &root);

  std::shared_ptr<Primitive> canvas;
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
