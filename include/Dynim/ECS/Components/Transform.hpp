#pragma once

#include <glm/vec2.hpp>

namespace Dynim {

class Transform {
public:
  Transform() : m_Position(0, 0), m_Scale(1, 1) {}
  Transform(glm::vec2 position) : m_Position(position), m_Scale(1, 1) {}
  Transform(glm::vec2 position, glm::vec2 scale) : m_Position(position), m_Scale(scale) {}

  glm::vec2 GetPosition() const { return m_Position; }
  void SetPosition(glm::vec2 position) { m_Position = position; }
  void Move(glm::vec2 translation) { m_Position += translation; }

  glm::vec2 GetScale() const { return m_Scale; }
  void SetScale(glm::vec2 scale) { m_Scale = scale; }
  void Scale(glm::vec2 scalar) { m_Scale *= scalar; }

  float GetRotation() const { return m_Rotation; }
  void SetRotation(float angle) { m_Rotation = angle; }
  void Rotate(float degress) { m_Rotation += degress; }

private:
  glm::vec2 m_Position, m_Scale;
  float m_Rotation = 0;
};

} // namespace Dynim
