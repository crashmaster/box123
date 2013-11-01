#include "KeyEventHandlingPolicy.hpp"
#include <stdlib.h>

bool KeyEventHandlingPolicy::handleKeyDownEvent(SDL_keysym* keysym) const {
  switch (keysym->sym) {
    case SDLK_ESCAPE:
      ::SDL_Quit();
      return false;
    default:
      break;
  }

  return true;
}
