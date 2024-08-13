#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/trigonometric.hpp>
#include <memory>

#include "constants.cpp"
#include "graph/graph.h"
#include "primitives/line.h"
#include "primitives/point.h"
#include "primitives/primitive.h"
#include "primitives/square.h"
#include "primitives/triangle.h"

namespace SceneProvider {

static std::unique_ptr<Primitive> GetSamleScene();
static std::unique_ptr<Graph> GetGraph();

}  // namespace SceneProvider

static std::unique_ptr<Primitive> SceneProvider::GetSamleScene() {
  auto root = std::make_unique<Square>();
  root->color = glm::vec4(0.25f);
  root->transform.scale = glm::vec3(1.5);

  auto point = std::make_unique<Point>();
  point->color = glm::vec4(0.0f);
  point->size = 10;
  point->transform.position = glm::vec3(0.1, 0, 0.1);

  auto triangle = std::make_shared<Triangle>();
  triangle->color = glm::vec4(1.0, 0.0, 0.0, 1.0);

  auto zSquare = std::make_shared<Square>();
  zSquare->transform.position = glm::vec3(0.25, 0.0, 0.0);
  zSquare->transform.rotation = glm::vec3(glm::radians(1.0), glm::radians(90.0), glm::radians(1.0));
  zSquare->transform.scale = glm::vec3(0.1, 0.1, 0.1);
  zSquare->color = glm::vec4(0.0, 0.0, 1.0, 0.1);

  auto ySquare = std::make_shared<Square>();
  ySquare->transform.position = glm::vec3(0.0, 0.25, 0.0);
  ySquare->transform.rotation = glm::vec3(glm::radians(90.0), 0.0, glm::radians(1.0));
  ySquare->transform.scale = glm::vec3(0.1, 0.1, 0.1);
  ySquare->color = glm::vec4(0.0, 1.0, 0.0, 0.1);

  auto x_line = std::make_shared<Line>(glm::vec3(-0.5, 0.0, 0.0), glm::vec3(0.5, 0.0, 0.0));
  x_line->color = glm::vec4(0.0);

  auto y_line = std::make_shared<Line>(glm::vec3(0.0, -0.5, 0.0), glm::vec3(0.0, 0.5, 0.0));
  y_line->color = glm::vec4(0.0);

  auto z_line = std::make_shared<Line>(glm::vec3(0.0, 0.0, -0.5), glm::vec3(0.0, 0.0, 0.5));
  z_line->color = glm::vec4(0.0);

  root->AddChild(triangle);
  triangle->AddChild(std::move(point));
  root->AddChild(x_line);
  root->AddChild(y_line);
  root->AddChild(z_line);
  root->AddChild(zSquare);
  root->AddChild(ySquare);

  return root;
}

#define INCLUDE_TIRANGLES 0

static std::unique_ptr<Graph> SceneProvider::GetGraph() {
  auto root = std::make_unique<Graph>();

  auto x_line = std::make_shared<Line>(constants::vec3::left, constants::vec3::right);
  x_line->color = constants::colors::blue;

  auto xPoint = std::make_shared<Point>();
  xPoint->transform.position = constants::vec3::left;
  xPoint->size = 20;
  xPoint->color = constants::colors::blue;
  root->AddChild(xPoint);

  auto y_line = std::make_shared<Line>(constants::vec3::up, constants::vec3::down);
  y_line->color = constants::colors::green;

  auto z_line = std::make_shared<Line>(constants::vec3::forward, constants::vec3::backward);
  z_line->color = constants::colors::red;

#if INCLUDE_TIRANGLES

  auto xTriangle = std::make_shared<Triangle>();
  xTriangle->color = constants::colors::blue * 0.25f;
  xTriangle->transform.rotation = glm::quat{glm::vec3{0.0, 0.0, glm::radians(-90.0)}};
  x_line->AddChild(xTriangle);

  auto yTriangle = std::make_shared<Triangle>();
  yTriangle->color = constants::colors::green * 0.25f;
  yTriangle->transform.rotation = glm::quat{glm::vec3{0.0, glm::radians(90.0), 0.0}};
  y_line->AddChild(yTriangle);

  auto zTriangle = std::make_shared<Triangle>();
  zTriangle->color = constants::colors::red * 0.25f;
  zTriangle->transform.rotation = glm::quat{glm::vec3{glm::radians(90.0), 0.0, 0.0}};
  z_line->AddChild(zTriangle);

#endif  // INCLUDE_TIRANGLES

  root->AddChild(x_line);
  root->AddChild(y_line);
  root->AddChild(z_line);

  return root;
}
