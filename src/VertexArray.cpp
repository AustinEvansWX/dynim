#define GL_GLEXT_PROTOTYPES

#include "VertexArray.hpp"

#include <GL/gl.h>
#include <GL/glext.h>

namespace Dynim {

VertexArray::VertexArray() {}
VertexArray::VertexArray(const void *vertices, unsigned int size, const unsigned int *indices, unsigned int count) {
  SetData(vertices, size, indices, count);
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &m_Id);
}

void VertexArray::SetData(const void *vertices, unsigned int size, const unsigned int *indices, unsigned int count) {
  m_Count = count;

  glGenVertexArrays(1, &m_Id);
  glBindVertexArray(m_Id);

  unsigned int vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

  unsigned int ibo;
  glGenBuffers(1, &ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArray::Bind() const {
  glBindVertexArray(m_Id);
}

void VertexArray::Unbind() const {
  glBindVertexArray(0);
}

} // namespace Dynim
