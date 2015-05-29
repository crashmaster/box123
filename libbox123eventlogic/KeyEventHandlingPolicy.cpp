#include "box123/KeyEventHandlingPolicy.hpp"


bool KeyEventHandlingPolicy::handleKeyDownEvent(SDL_Keysym* keysym) const {
  switch (keysym->sym) {
    case SDLK_ESCAPE:
      ::SDL_Quit();
      return false;
    default:
      break;
  }

  return true;
}
