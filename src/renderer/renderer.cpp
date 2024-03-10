#include "glad/glad.h"
#include "shader.h"

#include "renderer.h"

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <iostream>
#include <memory>
#include <ostream>

bool Renderer::Initialize() {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();

  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  CreateWindow();

  glfwMakeContextCurrent(window);

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();

  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return false;
  }

  glViewport(0, 0, start_width, start_height);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  triangle =
      std::unique_ptr<Shader>(new Shader(VERTEX_SHADER_PATH, FRAG_SHADER_PATH));

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  ui = GUI();

  return true;
}

void Renderer::Update() {

  ProcessEvents();

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  glm::vec4 color;
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  triangle->SetVec4Uniform("uColor", color);
  triangle->Use();
  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 3);

  ui.DrawColorWindow(color);
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  glfwSwapBuffers(window);
  glfwPollEvents();
}

bool Renderer::CreateWindow() {
  window = glfwCreateWindow(start_width, start_height, "GRAPHER", NULL, NULL);

  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return false;
  }

  return true;
}

// TODO: CREATE A FUNCTION IN A SEPARATE FILE FOR INPUT
void Renderer::ProcessEvents() {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
