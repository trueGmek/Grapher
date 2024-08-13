#include "camera/camera.h"
#include "cameraController/cameraController.h"
#include "renderer.h"
#include <cassert>
#include <memory>

void processEvents(GLFWwindow *window);

int main(int argc, char *argv[]) {

    std::shared_ptr<Camera> camera{new Camera()};
    CameraController cameraController{camera};

    Renderer renderer{camera};

    bool hasRendererInitialized = renderer.Initialize();

    assert(hasRendererInitialized);

    // MAIN LOOP
    while (renderer.IsClosing() == false) {
        cameraController.Tick();
        renderer.Update();
    }

    renderer.Finalize();
    return 0;
}
