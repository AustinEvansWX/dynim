#define GL_GLEXT_PROTOTYPES

#include "Dynim/Application.hpp"
#include "Dynim/ECS/Components/Mesh.hpp"
#include "Dynim/ECS/Components/Transform.hpp"
#include "shader.hpp"

#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
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
  m_Window = glfwCreateWindow(width, height, "Dynim", NULL, NULL);
  glfwMakeContextCurrent(m_Window);
  glfwSwapInterval(1);
  glfwSetWindowUserPointer(m_Window, this);
  glViewport(0, 0, width, height);
  glClearColor(0, 0, 0, 1);
}

void Application::ImportShader(string vertex_source_path, string fragment_source_path) {
  m_Shader_Program = CreateShaderProgram(vertex_source_path, fragment_source_path);
}

void Application::AddEntity(Entity *entity) {
  m_Entities.push_back(entity);
}

void Application::Run() {
  glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mod) {
    Application *app = (Application *)glfwGetWindowUserPointer(window);
    app->m_Keys[key] = action;
  });

  for (auto &entity : m_Entities) {
    for (auto &behaviour : entity->GetBehaviours()) {
      behaviour->Start(this, entity);
    }
  }

  double last = 0;
  double now = 0;

  glm::mat4 projection = glm::ortho(-300.0f, 300.0f, -300.0f, 300.0f);

  while (!glfwWindowShouldClose(m_Window)) {
    last = now;
    now = glfwGetTime();
    double delta_time = now - last;
    const string title = "Dynim | Frame Time: " + std::to_string(delta_time * 1000) + "ms";
    glfwSetWindowTitle(m_Window, title.c_str());

    glClear(GL_COLOR_BUFFER_BIT);

    for (auto &entity : m_Entities) {
      for (auto &behaviour : entity->GetBehaviours()) {
        behaviour->Update(this, entity, delta_time);
      }
    }

    glUseProgram(m_Shader_Program);
    int loc2 = glGetUniformLocation(m_Shader_Program, "mvp");

    for (auto &entity : m_Entities) {
      Mesh *mesh = entity->GetComponent<Mesh>();

      if (mesh == nullptr)
        continue;

      glm::mat4 model = glm::mat4(1.0f);

      Transform *transform = entity->GetComponent<Transform>();
      if (transform != nullptr) {
        glm::vec2 position = transform->GetPosition();
        glm::vec2 scale = transform->GetScale();
        model = glm::translate(model, glm::vec3(position, 0.0f));
        model = glm::scale(model, glm::vec3(scale, 0.0f));
      }

      glm::mat4 mvp = projection * model;

      glUniformMatrix4fv(loc2, 1, GL_FALSE, &mvp[0][0]);

      mesh->Bind();
      glDrawElements(GL_TRIANGLES, mesh->GetCount(), GL_UNSIGNED_INT, 0);
    }

    glfwSwapBuffers(m_Window);

    glUseProgram(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glfwPollEvents();
  }
}

void Application::Quit() {
  glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}

Application::~Application() {
  glfwDestroyWindow(m_Window);
  glfwTerminate();
}

} // namespace Dynim
