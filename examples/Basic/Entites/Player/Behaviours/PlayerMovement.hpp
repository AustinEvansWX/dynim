#pragma once

#include "Dynim/ECS/Behaviours/Behaviour.hpp"

using namespace Dynim;

class PlayerMovement : public Behaviour {
public:
  float m_Speed = 30.0f;

  void Update(void *app_ptr, void *entity_ptr, double delta_time) override;
};
