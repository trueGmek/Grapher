#include <memory>
#include "graph/graph.h"

class EquationView : public Primitive {
 private:
  std::weak_ptr<Graph> graph;

  char function_text[128]{"y = sin(x)"};

 public:
  void Draw(const glm::mat4& PV) override;

  EquationView(std::weak_ptr<Graph> graph);
};
