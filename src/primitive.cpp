#include <vector>
#define GL_GLEXT_PROTOTYPES

#include "primitive.hpp"

#include <GL/gl.h>
#include <GL/glext.h>

namespace Dynim {

void Primitive::Initialize() {
  glGenVertexArrays(1, &this->vao);
  glBindVertexArray(this->vao);

  glGenBuffers(1, &this->ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), this->indices.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &this->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(unsigned int), this->vertices.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Primitive::Draw() {
  glBindVertexArray(this->vao);
  glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
}

Triangle::Triangle() {
  this->vertices = {
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
  this->indices = {0, 1, 2};
  Initialize();
}

Quad::Quad() {
  //  this->vertices = {
  //      -0.5,
  //      -0.5,
  //      0,
  //      1,
  //
  //      0.5,
  //      -0.5,
  //      0,
  //      1,
  //
  //      0.5,
  //      0.5,
  //      0,
  //      1,
  //
  //      -0.5,
  //      0.5,
  //      0,
  //      1,
  //  };

  this->vertices = {
      -1,
      -1,
      0,
      1,

      1,
      -1,
      0,
      1,

      1,
      1,
      0,
      1,

      -1,
      1,
      0,
      1,
  };
  this->indices = {0, 1, 2, 2, 3, 0};
  Initialize();
}

} // namespace Dynim
