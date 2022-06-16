#include "GameController.hpp"
#include "Dynim/Application.hpp"

#include <GLFW/glfw3.h>

void GameController::Update(void *app_ptr, void *entity_ptr, double delta_time) {
  Application *app = (Application *)app_ptr;
  if (app->GetInput(GLFW_KEY_ESCAPE)) {
    app->Quit();
  }
}
