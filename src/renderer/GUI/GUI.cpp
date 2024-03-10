#include "GUI.h"
#include <GL/gl.h>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

GUI::GUI() {}

void GUI::DrawColorWindow(glm::vec4 &color) {

  bool my_tool_active = true;
  ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);

  float *colorArray = glm::value_ptr(color);

  if (ImGui::ColorEdit4("Color", colorArray)) {
    color.r = colorArray[0];
    color.g = colorArray[1];
    color.b = colorArray[2];
    color.a = colorArray[3];
  }

  ImGui::End();
}
