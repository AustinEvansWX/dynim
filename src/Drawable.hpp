#pragma once

#include "VertexArray.hpp"

namespace Dynim {

enum DrawableType {
  DrawableGeneric,
  DrawableTriangle,
  DrawableQuad
};

class Drawable {
public:
  VertexArray m_Vao;
  DrawableType m_Type = DrawableType::DrawableGeneric;

  Drawable();
  Drawable(VertexArray &vao);
};

class Triangle : public Drawable {
public:
  DrawableType m_Type = DrawableType::DrawableTriangle;

  Triangle();
};

class Quad : public Drawable {
public:
  DrawableType m_Type = DrawableType::DrawableQuad;

  Quad();
};

} // namespace Dynim
