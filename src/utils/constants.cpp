#pragma once
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <string>
namespace constants {

class shader {
public:
  inline static const std::string MVP{"MVP"};
  inline static const std::string time{"uTime"};
  inline static const std::string frequency{"uFrequency"};
  inline static const std::string speed{"uSpeed"};
  inline static const std::string amplitude{"uAmplitude"};
  inline static const std::string color{"uColor"};
  inline static const std::string vertices_per_point{"uVertices"};
  inline static const std::string distance_between_vertices{"uUnit"};
  inline static const std::string point_pixel_size{"uPointPixelSize"};
  inline static const std::string viewport_size{"uViewportSize"};
};

class colors {
public:
  inline static const glm::vec4 red{1.0, 0.0, 0.0, 1.0};
  inline static const glm::vec4 green{0.0, 1.0, 0.0, 1.0};
  inline static const glm::vec4 blue{0.0, 0.0, 1.0, 1.0};
  inline static const glm::vec4 white{1.0};
  inline static const glm::vec4 black{0.0, 0.0, 0.0, 1.0};
};

class vec3 {
public:
  inline static const glm::vec3 zero{0.0};

  inline static const glm::vec3 up{0.0, 1.0, 0.0};
  inline static const glm::vec3 down{0.0, -1.0, 0.0};

  inline static const glm::vec3 left{1.0, 0.0, 0.0};
  inline static const glm::vec3 right{-1.0, 0.0, 0.0};

  inline static const glm::vec3 forward{0.0, 0.0, 1.0};
  inline static const glm::vec3 backward{0.0, 0.0, -1.0};
};

class vec4 {
  inline static const glm::vec4 zero{0.0};
};

} // namespace constants
