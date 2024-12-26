#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

void errorCallbackFcn(int errorCode, const char *errMsg);

void errorCallbackFcn(int errorCode, const char *errMsg) {
  std::cerr << "Error: " << std::string(errMsg);
}

int main(int argc, char **argv) {
  // Set error error callback
  glfwSetErrorCallback(errorCallbackFcn);

  if (!glfwInit()) {
    std::cerr << "Fatal error: GLFW not initialized, exiting.";
    return -1;
  }

  // Create window
  auto window = glfwCreateWindow(640, 480, "Space Invaders", nullptr, nullptr);
  if (!window) {
    std::cerr << "Fatal error: Window not created, exiting.";
    glfwTerminate();
    return -1;
  }

  // Make this window active for all further actions
  glfwMakeContextCurrent(window);

  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // GLEW initialization
  auto init = glewInit();
  if (init != GLEW_OK) {
    std::cerr << "Fatal error: GLEW not initialized, exiting.";
    glfwTerminate();
    return -1;
  }

  // Game Loop
  glClearColor(1.0, 0.0, 0.0, 1.0);
  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Close window and exit normally
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
