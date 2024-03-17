#include "shader.h"
#include "glm/gtc/type_ptr.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string &vertexShaderPath,
               const std::string &fragmentShaderPath) {

  const std::string *vertexCode = ReadShader(vertexShaderPath);
  const std::string *fragmentCode = ReadShader(fragmentShaderPath);

  unsigned int vertex, fragment;
  LoadShader(&vertex, GL_VERTEX_SHADER, *vertexCode, vertexShaderPath);
  LoadShader(&fragment, GL_FRAGMENT_SHADER, *fragmentCode, fragmentShaderPath);

  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);

  CheckLinking(ID);

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  delete vertexCode;
  delete fragmentCode;
}

std::string *Shader::ReadShader(const std::string &pathToShader) {
  auto *code{new std::string()};
  std::ifstream fileStream;
  fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    std::stringstream stringStream;
    fileStream.open(pathToShader);
    stringStream << fileStream.rdbuf();

    std::string codeString = stringStream.str();

    *code = codeString;
    return code;
  } catch (std::ifstream::failure &e) {
    std::cout << "ERROR::SHADER::FILE_UNSUCCESSFULLY_READ:: " << pathToShader
              << std::endl;
  }

  return nullptr;
}

void Shader::LoadShader(unsigned int *shader, GLenum type,
                        const std::string &shaderSource,
                        const std::string &path) {
  std::string typeString =
      type == GL_FRAGMENT_SHADER ? "GL_FRAGMENT_SHADER" : "GL_VERTEX_SHADER";

  if (!CompileShader(shader, type, shaderSource)) {
    char infoLog[512];
    glGetShaderInfoLog(*shader, 512, nullptr, infoLog);
    std::cout << path << std::endl;
    std::cout << "ERROR::SHADER::" << typeString << "::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
}

int Shader::CompileShader(unsigned int *shader, GLenum type,
                          const std::string &shaderSource) {
  *shader = glCreateShader(type);

  const char *shaderCode = shaderSource.c_str();
  glShaderSource(*shader, 1, &shaderCode, nullptr);
  glCompileShader(*shader);

  int success;
  glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);

  return success;
}

void Shader::Use() const { glUseProgram(ID); }

void Shader::CheckLinking(unsigned int id) const {
  int status;
  char infoLog[512];

  glGetProgramiv(id, GL_LINK_STATUS, &status);

  if (status == GL_FALSE) {
    glGetProgramInfoLog(ID, 512, nullptr, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
}

void Shader::SetMat4Uniform(const std::string &name, glm::mat4 value) const {
  glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE,
                     glm::value_ptr(value));
}

void Shader::SetVec4Uniform(const std::string &name, glm::vec4 value) const {
  glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z,
              value.w);
}

void Shader::SetVec3Uniform(const std::string &name, glm::vec3 value) const {
  glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y,
              value.z);
}
