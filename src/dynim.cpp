#define GL_GLEXT_PROTOTYPES

#include "dynim.hpp"
#include "shader.hpp"

#include <GL/gl.h>
#include <GL/glext.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>

using namespace std;

namespace Dynim {

void Application::Initialize(const int width, const int height) {
  SDL_Init(SDL_INIT_VIDEO);

  window_ = SDL_CreateWindow("Test", 0, 0, width, height, SDL_WINDOW_OPENGL);
  SDL_GLContext context = SDL_GL_CreateContext(window_);

  glViewport(0, 0, width, height);
  glClearColor(0, 0, 0, 1);
}

void Application::ImportShader(string vertex_source_path, string fragment_source_path) {
  shader_program_ = CreateShaderProgram(vertex_source_path, fragment_source_path);
}

void Application::Run() {
  SDL_bool running = SDL_TRUE;

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
  glUseProgram(shader_program_);

  while (running) {
    float delta_time = GetDeltaTime();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        running = SDL_FALSE;
        break;
      }
    }

    glClear(GL_COLOR_BUFFER_BIT);

    // glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    SDL_GL_SwapWindow(window_);
    SDL_Delay(20);
  }
}

float Application::GetDeltaTime() {
  last_ = now_;
  now_ = SDL_GetPerformanceCounter();
  return (now_ - last_) / (float)SDL_GetPerformanceFrequency();
}

Application::~Application() {
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

} // namespace Dynim
