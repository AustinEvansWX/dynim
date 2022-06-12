#include "dynim.hpp"

using namespace Dynim;

int main() {
  Application app = Application();
  app.Initialize(600, 600);
  app.ImportShader("resources/gridvert.glsl", "resources/gridfrag.glsl");
  app.Run();
  return 0;
}
