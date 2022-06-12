#include "Drawable.hpp"
#include "VertexArray.hpp"

namespace Dynim {

Drawable::Drawable() {}
Drawable::Drawable(VertexArray &vao) : m_Vao(vao) {}

Triangle::Triangle() {
  float vertices[] = {
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
  unsigned int indices[] = {0, 1, 2};
  VertexArray vao(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(unsigned int));
  m_Vao = vao;
}

Quad::Quad() {
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
  m_Vao = vao;
}

} // namespace Dynim
