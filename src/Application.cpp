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

namespace Dynim {

Application::Application(std::string title, int width, int height) {
  glfwSetErrorCallback(error_callback);
  glfwInit();
  m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  glfwSetWindowUserPointer(m_Window, this);
  glfwMakeContextCurrent(m_Window);
  glfwSwapInterval(1);
  glViewport(0, 0, width, height);
  glClearColor(0, 0, 0, 1);
  glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mod) {
    Application *app = (Application *)glfwGetWindowUserPointer(window);
    app->m_Keys[key] = action;
  });
}

void Application::SetTitle(std::string title) {
  glfwSetWindowTitle(m_Window, title.c_str());
}

void Application::ImportShader(string vertex_source_path, string fragment_source_path) {
  m_Shader_Program = CreateShaderProgram(vertex_source_path, fragment_source_path);
}

void Application::AddEntity(Entity *entity) {
  m_Entities.push_back(entity);
}

void Application::Run() {
  StartEntities();

  glm::mat4 projection = glm::ortho(-300.0f, 300.0f, -300.0f, 300.0f);

  while (!glfwWindowShouldClose(m_Window)) {
    double delta_time = GetDeltaTime();

    glClear(GL_COLOR_BUFFER_BIT);

    UpdateEntities(delta_time);

    glUseProgram(m_Shader_Program);
    int loc2 = glGetUniformLocation(m_Shader_Program, "mvp");

    for (auto &entity : m_Entities) {
      Mesh *mesh = entity->GetComponent<Mesh>();

      if (mesh == nullptr)
        continue;

      glm::mat4 model = glm::mat4(1.0f);

      Transform *transform = entity->GetComponent<Transform>();
      if (transform != nullptr) {
        model = glm::translate(model, glm::vec3(transform->GetPosition(), 0.0f));
        model = glm::scale(model, glm::vec3(transform->GetScale(), 0.0f));
      }

      glm::mat4 mvp = projection * model;

      glUniformMatrix4fv(loc2, 1, GL_FALSE, &mvp[0][0]);

      mesh->Bind();
      glDrawElements(GL_TRIANGLES, mesh->GetCount(), GL_UNSIGNED_INT, 0);
    }

    UnbindAll();
    glfwSwapBuffers(m_Window);
    glfwPollEvents();
  }
}

double Application::GetDeltaTime() {
  m_Last = m_Now;
  m_Now = glfwGetTime();
  return m_Now - m_Last;
}

void Application::StartEntities() {
  for (auto &entity : m_Entities) {
    for (auto &behaviour : entity->GetBehaviours()) {
      behaviour->Start(this, entity);
    }
  }
}

void Application::UpdateEntities(double delta_time) {
  for (auto &entity : m_Entities) {
    for (auto &behaviour : entity->GetBehaviours()) {
      behaviour->Update(this, entity, delta_time);
    }
  }
}

void Application::UnbindAll() {
  glUseProgram(0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Application::Quit() {
  glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
}

Application::~Application() {
  glfwDestroyWindow(m_Window);
  glfwTerminate();
}

} // namespace Dynim
