#include "PlayerMovement.hpp"
#include "Dynim/ECS/Components/Transform.hpp"
#include "Dynim/ECS/Entity.hpp"
#include "dynim.hpp"

#include <GLFW/glfw3.h>

void PlayerMovement::Update(void *app_ptr, void *entity_ptr, double delta_time) {
  Application *app = (Application *)app_ptr;
  Entity *entity = (Entity *)entity_ptr;

  Transform *transform = entity->GetComponent<Transform>();

  m_Speed = app->GetInput(GLFW_KEY_LEFT_SHIFT) ? 60.0f : 30.0f;

  if (app->GetInput(GLFW_KEY_W) > 0) {
    transform->Move(glm::vec2(0, m_Speed * delta_time));
  }

  if (app->GetInput(GLFW_KEY_A) > 0) {
    transform->Move(glm::vec2(-m_Speed * delta_time, 0));
  }

  if (app->GetInput(GLFW_KEY_S) > 0) {
    transform->Move(glm::vec2(0, -m_Speed * delta_time));
  }

  if (app->GetInput(GLFW_KEY_D) > 0) {
    transform->Move(glm::vec2(m_Speed * delta_time, 0));
  }
}
