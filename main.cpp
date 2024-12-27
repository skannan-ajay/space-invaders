#include "AlienSprite.hpp"
#include "Buffer.hpp"
#include "BufferTexture.hpp"
#include "Shader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>
#include <source_location>
#include <string>

#define GL_ERROR_CASE(glerror)                                                 \
  case glerror:                                                                \
    snprintf(error, sizeof(error), "%s", #glerror)

inline void gl_debug(const char *file, int line) {
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    char error[128];

    switch (err) {
      GL_ERROR_CASE(GL_INVALID_ENUM);
      break;
      GL_ERROR_CASE(GL_INVALID_VALUE);
      break;
      GL_ERROR_CASE(GL_INVALID_OPERATION);
      break;
      GL_ERROR_CASE(GL_INVALID_FRAMEBUFFER_OPERATION);
      break;
      GL_ERROR_CASE(GL_OUT_OF_MEMORY);
      break;
    default:
      snprintf(error, sizeof(error), "%s", "UNKNOWN_ERROR");
      break;
    }

    fprintf(stderr, "%s - %s: %d\n", error, file, line);
  }
}

#undef GL_ERROR_CASE

void errorCallbackFcn(int errorCode, const char *errMsg);

void errorCallbackFcn(int errorCode, const char *errMsg) {
  std::cerr << "Error: " << std::string(errMsg);
}

int main(int argc, char **argv) {
  constexpr size_t width = 224;
  constexpr size_t height = 256;

  // Set error error callback
  glfwSetErrorCallback(errorCallbackFcn);

  if (!glfwInit()) {
    std::cerr << "Fatal error: GLFW not initialized, exiting.";
    return -1;
  }

  // Request latest available OpenGL version on this machine
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Create window
  auto window =
      glfwCreateWindow(width, height, "Space Invaders", nullptr, nullptr);
  if (!window) {
    std::cerr << "Fatal error: Window not created, exiting.";
    glfwTerminate();
    return -1;
  }

  // Make this window active for all further actions
  glfwMakeContextCurrent(window);

  // GLEW initialization
  glewExperimental = GL_TRUE;
  auto init = glewInit();
  if (init != GLEW_OK) {
    std::cerr << "Fatal error: GLEW not initialized, exiting.";
    glfwTerminate();
    return -1;
  }

  std::source_location srcLoc;
  gl_debug(srcLoc.file_name(), srcLoc.line());

  std::cout << "Using OpenGL: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "Renderer used: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;

  glClearColor(1.0, 0.0, 0.0, 1.0);

  // Create graphics buffer
  SpaceInvaders::Buffer buffer(width, height);
  buffer.clear();

  // Create texture for presenting buffer to OpenGL
  SpaceInvaders::BufferTexture texture(&buffer);

  // Create VAO for full screen triangle
  GLuint fullscreenTriangleVao;
  glGenVertexArrays(1, &fullscreenTriangleVao);

  // Create Shader for displaying the buffer
  SpaceInvaders::Shader shader;
  auto program = shader.getProgram();
  glUseProgram(*program);

  // Set uniform to texture
  GLint location = glGetUniformLocation(*program, "buffer");
  glUniform1i(location, 0);

  // Setup OpenGL
  glDisable(GL_DEPTH_TEST);
  glActiveTexture(GL_TEXTURE0);

  // Bind vertex array to VAO
  glBindVertexArray(fullscreenTriangleVao);

  // Prepare Game
  SpaceInvaders::AlienSprite enemy;

  // Game Loop
  while (!glfwWindowShouldClose(window)) {
    buffer.set(0, 128, 0);
    enemy.draw(&buffer, 112, 128);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA,
                    GL_UNSIGNED_INT_8_8_8_8, buffer.data());
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Cleanup before closing the window
  glfwDestroyWindow(window);
  glfwTerminate();
  glDeleteVertexArrays(1, &fullscreenTriangleVao);
  return 0;
}
