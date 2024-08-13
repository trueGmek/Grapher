#include "graph/graph.h"
#include <glm/ext/vector_float4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "primitives/primitive.h"

class GraphView : public Primitive {
 private:
  std::weak_ptr<Graph> graph;

 public:
  void Draw(const glm::mat4& PV) override;

  GraphView(std::weak_ptr<Graph> graph);

 private:
};
