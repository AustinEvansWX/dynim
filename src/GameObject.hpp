#pragma once

#include <glm/vec2.hpp>

namespace Dynim {

class GameObject {
public:
  glm::vec2 m_Transform;

  GameObject(glm::vec2 &transform) : m_Transform(transform){};

  virtual void Update();
  inline glm::vec2 GetTransform() const { return m_Transform; }
  inline void SetTransform(glm::vec2 &transform) { m_Transform = transform; }
};

} // namespace Dynim
