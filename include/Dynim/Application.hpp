#pragma once

#include "Dynim/ECS/Entity.hpp"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

namespace Dynim {

class Application {
public:
  std::vector<Entity *> m_Entities;

  void Initialize(const int width, const int height);
  void ImportShader(string vertex_source_path, string fragment_source_path);
  void AddEntity(Entity *entity);
  void Run();
  void Quit();
  inline int GetInput(int key) { return m_Keys[key]; }

  ~Application();

private:
  GLFWwindow *m_Window = NULL;
  GLuint m_Shader_Program = 0;
  std::unordered_map<int, int> m_Keys;
};

} // namespace Dynim
