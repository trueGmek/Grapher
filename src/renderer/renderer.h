#pragma once
#include "camera/camera.h"
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
  constexpr static const float start_width = 1600;
  constexpr static const float start_height = 1200;

  bool drawWireFrame = false;

private:
  unsigned int VBO, VAO;
  std::shared_ptr<Camera> camera;
  GLFWwindow *window;

public:
  Renderer(std::shared_ptr<Camera> camera);

  bool Initialize();
  void Update();
  void Finalize();
  bool IsClosing() { return glfwWindowShouldClose(window); }

private:
  void ProcessEvents();
  bool CreateWindow();
  void RenderScene(const std::shared_ptr<Primitive> &root);
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
