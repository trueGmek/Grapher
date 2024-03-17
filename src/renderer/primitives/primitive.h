#include "shader.h"
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>

class Primitive {
public:
  glm::vec3 Position{0.0f, 0.0f, 0.0f};
  glm::quat Rotation{1.0f, 0.0f, 0.0f, 0.0f};
  glm::vec3 Scale{1, 1, 1};

  virtual void Draw(const glm::mat4 &projection, const glm::mat4 &view) = 0;

  Primitive(const std::string &vertexShaderPath,
            const std::string &fragmentShaderPath)
      : shader(vertexShaderPath, fragmentShaderPath) {}

protected:
  unsigned int VBO, VAO;

  Shader shader;
};
