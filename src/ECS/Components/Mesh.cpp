#define GL_GLEXT_PROTOTYPES

#include "Dynim/ECS/Components/Mesh.hpp"

#include <GL/gl.h>
#include <GL/glext.h>

namespace Dynim {

Mesh::Mesh() {}

Mesh::Mesh(const void *vertices, unsigned int size, const unsigned int *indices, unsigned int count) : m_Count(count) {
  glGenVertexArrays(1, &m_Vao);
  glBindVertexArray(m_Vao);

  glGenBuffers(1, &m_Vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

  glGenBuffers(1, &m_Ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), indices, GL_STATIC_DRAW);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh() {
  glDeleteVertexArrays(1, &m_Vao);
  glDeleteBuffers(1, &m_Vbo);
  glDeleteBuffers(1, &m_Ibo);
}

void Mesh::Bind() const {
  glBindVertexArray(m_Vao);
}

void Mesh::Unbind() const {
  glBindVertexArray(0);
}

} // namespace Dynim
