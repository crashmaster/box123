#include <cstdio>
#include <LoggingPolicy.hpp>
#include <SDLVideoInitPolicy.hpp>
#include <OpenGLInitPolicy.hpp>
#include <VideoSurface.hpp>
#include <process_events.hpp>

typedef VideoSurface<LoggingPolicy,
                     SDLVideoInitPolicy,
                     OpenGLInitPolicy> myVideoSurfaceType;

extern void process_events();

int main(void) {
  myVideoSurfaceType myVideoSurface(400, 500);

  while (true) {
    process_events();
  }

  return 0;
}
