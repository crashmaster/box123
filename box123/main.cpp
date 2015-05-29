#include "box123/DrawPolicy.hpp"
#include "box123/EventProcessingPolicy.hpp"
#include "box123/KeyEventHandlingPolicy.hpp"
#include "box123/LoggingPolicy.hpp"
#include "box123/OpenGLInitPolicy.hpp"
#include "box123/SDLEventHandlingPolicy.hpp"
#include "box123/SDLVideoInitPolicy.hpp"
#include "box123/Scene.hpp"
#include "box123/VideoSurface.hpp"

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

Box123Scene SCENE;

void stepForEMCC() {
  SCENE.step();
}

int main(void) {
  Box123VideoSurface videoSurface(640, 480);
  if (!videoSurface.init()) {
    return 1;
  }

#ifdef EMSCRIPTEN
  emscripten_set_main_loop(stepForEMCC, 0, 1);
#else
  bool action = true;
  while (action) {
    action = SCENE.step();
  }
#endif

  return 0;
}
