#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "CreateBasicTriangle.h"
#include "CreateBasicSquare.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}

int main(int argc, char** argv){

  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " [S|T]\n";
    return -1;
  }

  bool renderSquareMode = false;
  if (argv[1][0] == 'S') {
    renderSquareMode = true;
  } else if (argv[1][0] == 'T') {
    renderSquareMode = false;
  } else {
    std::cout << "Invalid argument. Use 'S' for square or 'T' for triangle.\n";
    return -1;
  }

  if (!glfwInit()){
    std::cout << "Failed to initialize GLFW.\n";
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window;
  window = glfwCreateWindow(800, 600, "C++ OpenGL on Windows", NULL, NULL);
  if (window == NULL)  {
    std::cout << "Failed to open GLFW window.\n";
    return -1;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    std::cout << "Failed to initialize GLAD.\n";
    return -1;
  }

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  
  if (renderSquareMode) {
    renderSquare(window);
  } else {
    renderTriangle(window);
  }

  glfwTerminate();
  return 0;
}