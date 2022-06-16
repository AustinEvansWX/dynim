#pragma once

#include "Dynim/ECS/Entity.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace Dynim {

class Application {
public:
  std::vector<Entity *> m_Entities;

  Application(std::string title, int width, int height);
  ~Application();

  void SetTitle(std::string);
  void ImportShader(std::string vertex_source_path, std::string fragment_source_path);
  void AddEntity(Entity *entity);

  void Run();
  void Quit();

  inline int GetInput(int key) { return m_Keys[key]; }

private:
  GLFWwindow *m_Window = NULL;
  GLuint m_Shader_Program = 0;
  std::unordered_map<int, int> m_Keys;

  double m_Last = 0, m_Now = 0;

  double GetDeltaTime();

  void StartEntities();
  void UpdateEntities(double delta_time);

  void UnbindAll();
};

} // namespace Dynim
