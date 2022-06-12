#pragma once

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <string>

using namespace std;

namespace Dynim {

class Application {
public:
  void Initialize(const int width, const int height);
  void ImportShader(string vertex_source_path, string fragment_source_path);
  void Run();
  ~Application();

private:
  GLFWwindow *window_ = NULL;
  double now_ = 0;
  double last_ = 0;
  GLuint shader_program_ = 0;

  double GetDeltaTime();
  void DisplayFPS(double delta_time);
};

} // namespace Dynim
