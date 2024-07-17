#include "graph/graph.h"
#include "imgui.h"
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "constants.cpp"

class GraphView {
public:
  std::shared_ptr<Graph> graph;

  glm::vec4 color{};

  float speed{1};
  float frequency{10};
  float amplitude{0.25};

private:
public:
  void Draw() {
    ImGui::Begin("Graph");

    ImGui::SliderFloat("frequency", &frequency, 0, 100);
    ImGui::SliderFloat("speed", &speed, 1, 100);
    ImGui::SliderFloat("amplitude", &amplitude, 0, 2);

    float *colorArray = glm::value_ptr(color);

    if (ImGui::ColorEdit4("Color", colorArray)) {
      color.r = colorArray[0];
      color.g = colorArray[1];
      color.b = colorArray[2];
      color.a = colorArray[3];
    }

    ImGui::End();
  }

  void SetDataOnGraph() {
    graph->shader.SetVec4Uniform(constants::shader::color, color);
    graph->shader.SetFloatUniform(constants::shader::speed, speed);
    graph->shader.SetFloatUniform(constants::shader::amplitude, amplitude);
    graph->shader.SetFloatUniform(constants::shader::frequency, frequency);
  }

  GraphView() : graph({}){};
  GraphView(std::shared_ptr<Graph> graph) : graph(graph){};

private:
};
