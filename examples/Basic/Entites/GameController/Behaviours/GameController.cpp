#include "GameController.hpp"
#include "Dynim/Application.hpp"

#include <GLFW/glfw3.h>
#include <string>

void GameController::Update(void *app_ptr, void *entity_ptr, double delta_time) {
  Application *app = (Application *)app_ptr;

  std::string title = "Basic Example | Frame Time: " + std::to_string(delta_time * 1000) + "ms";
  app->SetTitle(title);

  if (app->GetInput(GLFW_KEY_ESCAPE)) {
    app->Quit();
  }
}
