#include "SDLEventHandlingPolicy.hpp"

int SDLEventHandlingPolicy::SDL_PollEvent(SDL_Event* event) const {
  return ::SDL_PollEvent(event);
}

void SDLEventHandlingPolicy::handleQuit() const {
  ::SDL_Quit();
  ::exit(0);
}