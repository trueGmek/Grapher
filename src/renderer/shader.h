#pragma once

#include "glad/glad.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
#include <string>

class Shader {
public:
  unsigned int ID;
  Shader(const std::string &vertexShaderPath,
         const std::string &fragmentShaderPath);

  Shader(const std::string &vertexShaderPath,
         const std::string &fragmentShaderPath,
         const std::string &geometryShaderPath);

  void AttachGeometryShader(const std::string &path);

  void Use() const;
  void SetMat4Uniform(const std::string &name, const glm::mat4 value) const;
  void SetVec4Uniform(const std::string &name, const glm::vec4 value) const;
  void SetVec3Uniform(const std::string &name, const glm::vec3 value) const;
  void SetVec2Uniform(const std::string &name, const glm::vec2 value) const;
  void SetFloatUniform(const std::string &name,const float value) const;

private:
  static void LoadShader(unsigned int *shader, GLenum type,
                         const std::string &shaderSource,
                         const std::string &path);

  static int CompileShader(unsigned int *shader, GLenum type,
                           const std::string &shaderSource);

  static std::string *ReadShader(const std::string &pathToShader);
  void CheckLinking(unsigned int id) const;
};
