#pragma once
#include "GUI/GUI.h"
#include "shader.h"
#include <GLFW/glfw3.h>
#include <cstddef>
#include <memory>

class Renderer {
public:
  Renderer(){};

  bool Initialize();
  void Update();
  void Finalize();

  bool IsClosing() { return glfwWindowShouldClose(window); }

private:
  GUI ui;
  unsigned int VBO, VAO;

  std::unique_ptr<Shader> triangle;
  GLFWwindow *window = nullptr;

  void ProcessEvents();
  bool CreateWindow();

  const std::string VERTEX_SHADER_PATH = "./resources/shaders/triangle.vert";
  const std::string FRAG_SHADER_PATH = "./resources/shaders/triangle.frag";

  const float vertices[9] = {
      -0.5f, -0.5f, 0.0f, //
      0.5f,  -0.5f, 0.0f, //
      0.0f,  0.5f,  0.0f  //
  };

  const float start_width = 1600;
  const float start_height = 1200;
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
