#pragma once

#include "Dynim/ECS/Behaviours/Behaviour.hpp"

using namespace Dynim;

class GameController : public Behaviour {
public:
  void Update(void *app_ptr, void *entity_ptr, double delta_time) override;
};
