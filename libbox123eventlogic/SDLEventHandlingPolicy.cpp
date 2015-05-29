#include "box123/SDLEventHandlingPolicy.hpp"


int SDLEventHandlingPolicy::SDL_PollEvent(SDL_Event* event) const {
  return ::SDL_PollEvent(event);
}

bool SDLEventHandlingPolicy::handleQuit() const {
  ::SDL_Quit();
  return false;
}
