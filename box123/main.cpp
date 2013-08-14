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

typedef VideoSurface<LoggingPolicy,
                     SDLVideoInitPolicy,
                     OpenGLInitPolicy> MyVideoSurfaceType;

typedef EventProcessingPolicy<SDLEventHandlingPolicy,
                              KeyEventHandlingPolicy> EventProcessingPolicyType;

typedef Scene<EventProcessingPolicyType, DrawPolicy> MySceneType;

#ifdef EMSCRIPTEN
  MySceneType* scenePtr = 0;

  void stepForEMCC() {
    scenePtr->step();
  }
#endif

int main(void) {
  MyVideoSurfaceType myVideoSurface(640, 480);
  myVideoSurface.init();

  MySceneType myScene;

#ifdef EMSCRIPTEN
  scenePtr = &myScene;
  emscripten_set_main_loop(stepForEMCC, 0, 1);
#else
  while (true) {
    myScene.step();
  }
#endif

  return 0;
}
