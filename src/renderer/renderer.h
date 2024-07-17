#pragma once
#include "primitives/primitive.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/quaternion.hpp>
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
  unsigned int VBO, VAO;
  float azimuth{};
  float polar{};
  float radius = 3.0f;

  GLFWwindow *window = nullptr;

  void ProcessEvents();
  bool CreateWindow();
  void RenderScene(const std::shared_ptr<Primitive> &root);

  void inside_scroll_callback(GLFWwindow *window, double xoffset,
                              double yoffset);
};

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
