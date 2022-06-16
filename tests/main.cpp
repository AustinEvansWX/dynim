#include "Dynim/ECS/Behaviours/Behaviour.hpp"
#include "Dynim/ECS/Components/Mesh.hpp"
#include "Dynim/ECS/Components/Transform.hpp"
#include "Dynim/ECS/Entity.hpp"
#include "dynim.hpp"

#include <glm/vec2.hpp>
#include <iostream>

using namespace Dynim;

int main() {
  Application app = Application();
  app.Initialize(600, 600);
  app.ImportShader("resources/vert.glsl", "resources/frag.glsl");

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

  Mesh mesh(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(unsigned int));

  Transform player_transform;
  player_transform.Scale(glm::vec2(50.0f, 50.0f));

  Entity entity;

  Behaviour movement;

  movement.OnUpdate([&entity](void *app_ptr, double delta_time) {
    Application *app = (Application *)app_ptr;

    float speed = 5.0f;

    if (app->GetInput(GLFW_KEY_W) > 0) {
      entity.GetComponent<Transform>()->Move(glm::vec2(0, speed * delta_time));
    }

    if (app->GetInput(GLFW_KEY_A) > 0) {
      entity.GetComponent<Transform>()->Move(glm::vec2(-speed * delta_time, 0));
    }

    if (app->GetInput(GLFW_KEY_S) > 0) {
      entity.GetComponent<Transform>()->Move(glm::vec2(0, -speed * delta_time));
    }

    if (app->GetInput(GLFW_KEY_D) > 0) {
      entity.GetComponent<Transform>()->Move(glm::vec2(speed * delta_time, 0));
    }
  });

  entity.AddBehaviour(&movement);

  entity.AddComponent(&player_transform);
  entity.AddComponent(&mesh);

  app.AddEntity(&entity);
  app.Run();

  return 0;
}
