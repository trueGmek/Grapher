#include "graph/graph.h"
#include "primitives/line.h"
#include "primitives/point.h"
#include "primitives/primitive.h"
#include "primitives/square.h"
#include "primitives/triangle.h"
#include <glm/ext/vector_float3.hpp>
#include <memory>

namespace SceneProvider {

static std::unique_ptr<Primitive> GetSamleScene();
static std::unique_ptr<Primitive> GetWorkingScene();
static std::unique_ptr<Graph> GetGraph();

} // namespace SceneProvider

static std::unique_ptr<Primitive> SceneProvider::GetSamleScene() {

  auto root = std::make_unique<Square>();
  root->color = glm::vec4(0.25f);
  root->transform.scale = glm::vec3(1.5);

  auto point = std::make_unique<Point>();
  point->color = glm::vec4(0.0f);
  point->size = 10;

  auto triangle = std::make_shared<Triangle>();
  triangle->color = glm::vec4(1.0, 0.0, 0.0, 1.0);

  auto x_line = std::make_shared<Line>(glm::vec3(-0.5, 0.0, 0.0),
                                       glm::vec3(0.5, 0.0, 0.0));

  auto y_line = std::make_shared<Line>(glm::vec3(0.0, -0.5, 0.0),
                                       glm::vec3(0.0, 0.5, 0.0));

  auto z_line = std::make_shared<Line>(glm::vec3(0.0, 0.0, -0.5),
                                       glm::vec3(0.0, 0.0, 0.5));

  root->AddChild(triangle);
  triangle->AddChild(std::move(point));
  root->AddChild(x_line);
  root->AddChild(y_line);
  root->AddChild(z_line);

  return root;
}

static std::unique_ptr<Primitive> SceneProvider::GetWorkingScene() {
  auto root = std::make_unique<Graph>();
  root->size = 10;
  return root;
}

static std::unique_ptr<Graph> SceneProvider::GetGraph() {
  auto root = std::make_unique<Graph>();
  root->size = 10;
  return root;
}
