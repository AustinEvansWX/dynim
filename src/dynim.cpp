#include "GameObject.hpp"
#define GL_GLEXT_PROTOTYPES

#include "Drawable.hpp"
#include "VertexArray.hpp"
#include "dynim.hpp"
#include "shader.hpp"

#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
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
  float vertices[] = {
      -0.5,
      -0.5,
      0,
      1,

      0.5,
      -0.5,
      0,
      1,

      0.5,
      0.5,
      0,
      1,

      -0.5,
      0.5,
      0,
      1,
  };
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};
  VertexArray vao(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(unsigned int));

  glm::vec2 pos(1, 1);
  GameObject player(pos);

  game_objects_.push_back(player);

  glfwSwapInterval(1);

  glfwSetWindowUserPointer(window_, this);

  glfwSetKeyCallback(window_, [](GLFWwindow *window, int key, int scancode, int action, int mod) {
    Application *app = (Application *)glfwGetWindowUserPointer(window);
    if (action == GLFW_PRESS) {
      switch (key) {
      case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;

        //      case GLFW_KEY_W:
        //        app->player_->m_Transform.y += 0.1f;
        //        break;
        //
        //      case GLFW_KEY_A:
        //        app->player_->m_Transform.x -= 0.1f;
        //        break;
        //
        //      case GLFW_KEY_S:
        //        app->player_->m_Transform.y -= 0.1f;
        //        break;
        //
        //      case GLFW_KEY_D:
        //        app->player_->m_Transform.x += 0.1f;
        //        break;
      }
    }
  });

  while (!glfwWindowShouldClose(window_)) {
    double delta_time = GetDeltaTime();
    DisplayFrameTime(delta_time);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program_);

    for (auto &game_object : game_objects_) {
      game_object.Update();

      int loc = glGetUniformLocation(shader_program_, "transform");
      glUniform2fv(loc, 1, &game_object.m_Transform[0]);

      vao.Bind();
      glDrawElements(GL_TRIANGLES, vao.GetCount(), GL_UNSIGNED_INT, 0);
    }

    LoopCleanup();
  }
}

double Application::GetDeltaTime() {
  last_ = now_;
  now_ = glfwGetTime();
  return now_ - last_;
}

void Application::DisplayFrameTime(double delta_time) {
  const string title = "Frame Time: " + std::to_string(delta_time * 1000) + "ms";
  glfwSetWindowTitle(window_, title.c_str());
}

void Application::LoopCleanup() {
  glfwSwapBuffers(window_);
  glBindVertexArray(0);
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
