#pragma once

#include <GL/glew.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
namespace SpaceInvaders {
/**
 * OpenGL Shader to display buffers
 */
class Shader {
public:
  Shader() = default;
  Shader(const std::string &aVertexShaderSrc,
         const std::string &aFragmentShaderSrc)
      : fVertexShaderSrc(aVertexShaderSrc),
        fFragmentShaderSrc(aFragmentShaderSrc) {}

  enum class Status { UNCOMPILED, COMPILATION_COMPLETE, COMPILED_WITH_ERRORS };

  GLuint *getProgram() {
    setupVertexShader();
    setupFragmentShader();
    try {
      linkAndValidateProgram();
    } catch (std::runtime_error err) {
      std::cerr << err.what();
      throw;
    }
    return fShaderId.get();
  }

private:
  void setupVertexShader();
  void setupFragmentShader();
  void validateShader(GLuint aShaderId, const std::string &aShaderSrc);
  void linkAndValidateProgram();

  std::string fVertexShaderSrc{
      "\n"
      "#version 330\n"
      "\n"
      "noperspective out vec2 TexCoord;\n"
      "\n"
      "void main(void){\n"
      "\n"
      "    TexCoord.x = (gl_VertexID == 2)? 2.0: 0.0;\n"
      "    TexCoord.y = (gl_VertexID == 1)? 2.0: 0.0;\n"
      "    \n"
      "    gl_Position = vec4(2.0 * TexCoord - 1.0, 0.0, 1.0);\n"
      "}\n"};

  std::string fFragmentShaderSrc{
      "\n"
      "#version 330\n"
      "\n"
      "uniform sampler2D buffer;\n"
      "noperspective in vec2 TexCoord;\n"
      "\n"
      "out vec3 outColor;\n"
      "\n"
      "void main(void){\n"
      "    outColor = texture(buffer, TexCoord).rgb;\n"
      "}\n"};

  std::unique_ptr<GLuint> fShaderId{
      std::make_unique<GLuint>(glCreateProgram())};
  Status fStatus{Shader::Status::UNCOMPILED};
};
} // namespace SpaceInvaders
