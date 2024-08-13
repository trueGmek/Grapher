#include "renderer.h"
#include "GUI/GUI.h"
#include "GUI/graphView.h"
#include "glad/glad.h"
#include "input.h"
#include "primitives/primitive.h"
#include "sceneProvider.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/ext/vector_float2.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iostream>
#include <memory>
#include <ostream>

std::shared_ptr<Primitive> root;
GraphView graphView;

Renderer::Renderer(std::shared_ptr<Camera> camera) : camera(std::shared_ptr<Camera>(camera)) {}

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
  glfwSetWindowUserPointer(window, this);
  glfwMakeContextCurrent(window);

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init();

  if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == false) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return false;
  }

  glViewport(0, 0, start_width, start_height);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  std::shared_ptr<Graph> graph = SceneProvider::GetGraph();
  root = graph;
  // TODO: GET THIS FROM HERE
  graphView = GraphView(graph);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if (drawWireFrame) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  return true;
}

void Renderer::Update() {
  ProcessEvents();

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

  glClear(GL_COLOR_BUFFER_BIT);

  graphView.Draw();
  graphView.SetDataOnGraph();
  RenderScene(root);

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  glfwSwapBuffers(window);
  glfwPollEvents();
}

void Renderer::RenderScene(const std::shared_ptr<Primitive> &root) {
  root->DrawRecursive(camera->GetPVMatrix(), glfwGetTime());
}

bool Renderer::CreateWindow() {
  window = glfwCreateWindow(start_width, start_height, "GRAPHER", NULL, NULL);

  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return false;
  }

  Input::window = window;

  viewport_width = start_width;
  viewport_height = start_height;

  return true;
}

void Renderer::Finalize() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
}

glm::vec2 Renderer::GetViewportSize() { return glm::vec2{viewport_width, viewport_height}; }

// TODO: CREATE A FUNCTION IN A SEPARATE FILE FOR INPUT
// TODO: ADD A WRAPPER FOR GlfwWindow THAT WOULD HAVE SUCH FUNCTIONALITY
void Renderer::ProcessEvents() {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  auto renderer = (Renderer *)glfwGetWindowUserPointer(window);
  glViewport(0, 0, width, height);

  Renderer::viewport_width = width;
  Renderer::viewport_height = height;
}
