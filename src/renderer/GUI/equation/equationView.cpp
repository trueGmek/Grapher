#include "equationView.h"
#include <imgui.h>
#include <memory>
#include "primitives/primitive.h"

const std::string VERTEX_SHADER_PATH{"../resources/shaders/point.vert"};
const std::string FRAGMENT_SHADER_PATH{"../resources/shaders/point.frag"};

EquationView::EquationView(std::weak_ptr<Graph> graph) : Primitive(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH) {
  this->graph = graph;
}

void EquationView::Draw(const glm::mat4& PV) {
  ImGui::InputText("Equation", function_text, 128);

  if (ImGui::Button("Validate")) {
  }

  if (ImGui::Button("Generate")) {
  }
}
