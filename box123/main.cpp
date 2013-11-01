#include "LoggingPolicy.hpp"
#include "SDLVideoInitPolicy.hpp"
#include "OpenGLInitPolicy.hpp"
#include "VideoSurface.hpp"

#include "SDLEventHandlingPolicy.hpp"
#include "KeyEventHandlingPolicy.hpp"
#include "EventProcessingPolicy.hpp"
#include "DrawPolicy.hpp"
#include "Scene.hpp"

#ifdef EMSCRIPTEN
  #include <emscripten.h>
#endif

typedef SDLVideoInitPolicy<LoggingPolicy> SDLVideoInitPolicyWithLogging;
typedef OpenGLInitPolicy<LoggingPolicy> OpenGLInitPolicyWithLogging;
typedef VideoSurface<SDLVideoInitPolicyWithLogging,
                     OpenGLInitPolicyWithLogging> Box123VideoSurface;

typedef EventProcessingPolicy<SDLEventHandlingPolicy,
                              KeyEventHandlingPolicy> SDLAndKeyEventProcessingPolicy;
typedef Scene<SDLAndKeyEventProcessingPolicy, DrawPolicy> Box123Scene;

Box123VideoSurface VIDEO_SURFACE(640, 480);
Box123Scene SCENE;

void stepForEMCC() {
  SCENE.step();
}

int main(void) {
#ifdef EMSCRIPTEN
  emscripten_set_main_loop(stepForEMCC, 0, 1);
#else
  while (true) {
    SCENE.step();
  }
#endif

  return 0;
}
