#include "glad/glad.h"

#include "renderer.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "primitives/primitive.h"
#include "sceneProvider.h"

#include "../utils/constants.cpp"

#include <iostream>
#include <memory>
#include <ostream>

#define GLM_ENABLE_EXPERIMENTAL

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

  root = std::shared_ptr(SceneProvider::GetWorkingScene());

  ui = GUI();

  if (drawWireFrame) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
  return true;
}

glm::vec4 color;

void Renderer::Update() {

  float aspect = Renderer::start_width / Renderer::start_height;

  projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, 0.1f, 10.0f);
  view = glm::translate(glm::mat4{1.0f}, glm::vec3{0, 0, -1});

  ProcessEvents();

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);

  RenderScene(root);
  ui.DrawColorWindow(color);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  glfwSwapBuffers(window);
  glfwPollEvents();
}

void Renderer::RenderScene(const std::shared_ptr<Primitive> &root) {
  auto PV = projection * view;
  root->shader.SetFloatUniform(constants::shader::time, glfwGetTime());
  root->DrawRecursive(PV);
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

void Renderer::Finalize() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
