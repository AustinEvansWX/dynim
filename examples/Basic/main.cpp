#include "Dynim/Application.hpp"
#include "Dynim/ECS/Behaviours/Behaviour.hpp"
#include "Dynim/ECS/Components/Mesh.hpp"
#include "Dynim/ECS/Components/Transform.hpp"
#include "Dynim/ECS/Entity.hpp"
#include "Entites/GameController/Behaviours/GameController.hpp"
#include "Entites/Player/Behaviours/PlayerMovement.hpp"

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

  PlayerMovement movement;

  Entity player;
  player.AddBehaviour(&movement);
  player.AddComponent(&player_transform);
  player.AddComponent(&mesh);
  app.AddEntity(&player);

  Entity game_controller;
  GameController controller;
  game_controller.AddBehaviour(&controller);
  app.AddEntity(&game_controller);

  app.Run();

  return 0;
}
