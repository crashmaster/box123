#include "LoggingPolicy.hpp"
#include "SDLVideoInitPolicy.hpp"
#include "OpenGLInitPolicy.hpp"
#include "VideoSurface.hpp"

#include "SDLEventHandlingPolicy.hpp"
#include "KeyEventHandlingPolicy.hpp"
#include "EventProcessingPolicy.hpp"
#include "DrawPolicy.hpp"
#include "Scene.hpp"

typedef VideoSurface<LoggingPolicy,
                     SDLVideoInitPolicy,
                     OpenGLInitPolicy> MyVideoSurfaceType;

typedef EventProcessingPolicy<SDLEventHandlingPolicy,
                              KeyEventHandlingPolicy> EventProcessingPolicyType;

typedef Scene<EventProcessingPolicyType, DrawPolicy> MySceneType;

int main(void) {
  MyVideoSurfaceType myVideoSurface(640, 480);
  myVideoSurface.init();

  MySceneType myScene;

#ifndef EMSCRIPTEN
  while (true) {
    myScene.step();
  }
#else
  emscripten_set_main_loop(tick, 0, 1);
#endif

  return 0;
}
