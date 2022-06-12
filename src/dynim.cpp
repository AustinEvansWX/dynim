#define GL_GLEXT_PROTOTYPES

#include "dynim.hpp"
#include "shader.hpp"

#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

static void error_callback(int error, const char *description) {
  fprintf(stderr, "Error: %s\n", description);
}

using namespace std;

namespace Dynim {

void Application::Initialize(const int width, const int height) {
  glfwSetErrorCallback(error_callback);
  glfwInit();
  window_ = glfwCreateWindow(width, height, "Dynim", NULL, NULL);
  glfwMakeContextCurrent(window_);

  glViewport(0, 0, width, height);
  glClearColor(0, 0, 0, 1);
}

void Application::ImportShader(string vertex_source_path, string fragment_source_path) {
  shader_program_ = CreateShaderProgram(vertex_source_path, fragment_source_path);
}

void Application::Run() {
  float triangle[] = {
      0,
      0.5,
      0,
      1,

      -0.5,
      -0.5,
      0,
      1,

      0.5,
      -0.5,
      0,
      1,
  };

  float quad[] = {
      -0.5,
      0.5,
      0,
      1,

      -0.5,
      -0.5,
      0,
      1,

      0.5,
      0.5,
      0,
      1,

      0.5,
      -0.5,
      0,
      1,
  };

  GLuint indices[] = {0, 1, 2, 2, 1, 3};

  GLuint vertex_buffer;
  glGenBuffers(1, &vertex_buffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

  GLuint index_buffer;
  glGenBuffers(1, &index_buffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(window_)) {
    double delta_time = GetDeltaTime();
    DisplayFPS(delta_time);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program_);
    // glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    LoopCleanup();
  }
}

double Application::GetDeltaTime() {
  last_ = now_;
  now_ = glfwGetTime();
  return now_ - last_;
}

void Application::DisplayFPS(double delta_time) {
  int fps = 1 / delta_time;
  const string title = "FPS: " + std::to_string(fps);
  glfwSetWindowTitle(window_, title.c_str());
}

void Application::LoopCleanup() {
  glfwSwapBuffers(window_);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glUseProgram(0);
  glfwPollEvents();
}

Application::~Application() {
  glfwDestroyWindow(window_);
  glfwTerminate();
}

} // namespace Dynim
