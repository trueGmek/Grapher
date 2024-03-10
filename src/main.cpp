#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "renderer.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <glm/ext/vector_float4.hpp>

void processEvents(GLFWwindow *window);

int main(int argc, char *argv[]) {

  Renderer renderer = Renderer();

  bool hasRendererInitialized = renderer.Initialize();

  assert(hasRendererInitialized);


  // MAIN LOOP
  while (renderer.IsClosing() == false) {
    renderer.Update();
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();

  return 0;
}
