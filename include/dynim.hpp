#pragma once

#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_stdinc.h>
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
  SDL_Window *window_ = NULL;
  Uint64 now_ = 0;
  Uint64 last_ = 0;
  GLuint shader_program_ = 0;

  float GetDeltaTime();
};

} // namespace Dynim
