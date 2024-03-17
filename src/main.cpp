#include "renderer.h"
#include <cassert>

void processEvents(GLFWwindow *window);

int main(int argc, char *argv[]) {

  Renderer renderer = Renderer();

  bool hasRendererInitialized = renderer.Initialize();

  assert(hasRendererInitialized);

  // MAIN LOOP
  while (renderer.IsClosing() == false) {
    renderer.Update();
  }

  renderer.Finalize();
  return 0;
}
