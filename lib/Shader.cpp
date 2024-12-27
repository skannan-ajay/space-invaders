#include "Shader.hpp"
#include <exception>
#include <iostream>
#include <stdexcept>

namespace SpaceInvaders {

void Shader::setupVertexShader() {
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  auto src = fVertexShaderSrc.c_str();
  glShaderSource(vertexShader, 1, &src, 0);
  glCompileShader(vertexShader);
  validateShader(vertexShader, fVertexShaderSrc);
  glAttachShader(*fShaderId.get(), vertexShader);
  glDeleteShader(vertexShader);
}

void Shader::setupFragmentShader() {
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  auto src = fFragmentShaderSrc.c_str();
  glShaderSource(fragmentShader, 1, &src, 0);
  glCompileShader(fragmentShader);
  validateShader(fragmentShader, fFragmentShaderSrc);
  glAttachShader(*fShaderId.get(), fragmentShader);
  glDeleteShader(fragmentShader);
}

void Shader::validateShader(GLuint aShaderId, const std::string &aShaderSrc) {
  constexpr unsigned BUFFER_SIZE{512};
  char buffer[BUFFER_SIZE];
  GLsizei len = 0;
  glGetShaderInfoLog(aShaderId, BUFFER_SIZE, &len, buffer);
  if (len > 0) {
    std::cerr << "Shader compile error: " << "ID: " << aShaderId
              << " Log: " << buffer;
  }
}

void Shader::linkAndValidateProgram() {
  glLinkProgram(*fShaderId.get());
  constexpr unsigned BUFFER_SIZE = 512;
  GLchar buffer[BUFFER_SIZE];
  GLsizei len = 0;
  glGetProgramInfoLog(*fShaderId.get(), BUFFER_SIZE, &len, buffer);
  if (len > 0) {
    std::string diag(std::string("Detected link error: ") +
                     std::string(buffer));
    throw std::runtime_error(diag);
  }
}
} // namespace SpaceInvaders
