#include "graphView.h"
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

const std::string VERTEX_SHADER_PATH{"../resources/shaders/point.vert"};
const std::string FRAGMENT_SHADER_PATH{"../resources/shaders/point.frag"};

void GraphView::Draw(const glm::mat4& PV) {
  if (auto lockedGraph = graph.lock()) {
    ImGui::Begin("Graph");

    ImGui::SliderFloat("frequency", &lockedGraph->frequency, 0, 100);
    ImGui::SliderFloat("speed", &lockedGraph->speed, 1, 100);
    ImGui::SliderFloat("amplitude", &lockedGraph->amplitude, 0, 2);
    ImGui::SliderInt("vertices per point", &lockedGraph->vertices_per_point, 1, 32);
    ImGui::SliderInt("points_z", &lockedGraph->points.x, 1, 32);
    ImGui::SliderInt("points_x", &lockedGraph->points.y, 1, 300);
    ImGui::SliderFloat("distance_between_vertices", &lockedGraph->distance_between_vertices, 0, 1);
    ImGui::SliderFloat3("Graph Position", glm::value_ptr(lockedGraph->transform.position), -1.0f, 1.0f);

    float* colorArray = glm::value_ptr(lockedGraph->color);

    if (ImGui::ColorEdit4("Color", colorArray)) {
      lockedGraph->color.r = colorArray[0];
      lockedGraph->color.g = colorArray[1];
      lockedGraph->color.b = colorArray[2];
      lockedGraph->color.a = colorArray[3];
    }


    if (ImGui::Button("Regenerate buffers")) {
      lockedGraph->SetBuffers();
    }

    ImGui::End();
  }
}

GraphView::GraphView(std::weak_ptr<Graph> graph) : Primitive(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH) {
  this->graph = graph;
};
