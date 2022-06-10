#define GL_GLEXT_PROTOTYPES

#include "shader.hpp"

#include <GL/gl.h>
#include <GL/glext.h>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace Dynim {

GLuint CreateShaderProgram(string vertex_source_path, string fragment_source_path) {
  vector<GLuint> shaders = {};

  const string vertex_shader_source = ReadShaderSource(vertex_source_path);
  const string fragment_shader_source = ReadShaderSource(fragment_source_path);

  shaders.push_back(CompileShader(GL_VERTEX_SHADER, vertex_shader_source));
  shaders.push_back(CompileShader(GL_FRAGMENT_SHADER, fragment_shader_source));

  GLuint program = LinkShaders(shaders);

  for (auto &shader : shaders) {
    glDeleteShader(shader);
  }

  return program;
}

string ReadShaderSource(string path) {
  ifstream shader(path);
  stringstream shader_buffer;
  shader_buffer << shader.rdbuf();
  return shader_buffer.str();
}

GLuint CompileShader(GLenum shader_type, const string &shader_source) {
  GLuint shader = glCreateShader(shader_type);
  const char *shader_source_data = shader_source.c_str();
  glShaderSource(shader, 1, &shader_source_data, NULL);
  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

  if (status == GL_FALSE) {
    GLint info_log_length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);

    GLchar *info_log = new GLchar[info_log_length + 1];
    glGetShaderInfoLog(shader, info_log_length, NULL, info_log);

    fprintf(stderr, "Error compiling shader: %s", info_log);

    delete[] info_log;
  }

  return shader;
}

GLuint LinkShaders(vector<GLuint> &shaders) {
  GLuint program = glCreateProgram();

  for (auto &shader : shaders) {
    glAttachShader(program, shader);
  }

  glLinkProgram(program);

  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);

  if (status == GL_FALSE) {
    GLint info_log_length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);

    GLchar *info_log = new GLchar[info_log_length + 1];
    glGetProgramInfoLog(program, info_log_length, NULL, info_log);

    fprintf(stderr, "Error linking program: %s", info_log);

    delete[] info_log;
  }

  for (auto &shader : shaders) {
    glDetachShader(program, shader);
  }

  return program;
}

} // namespace Dynim
