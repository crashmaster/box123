#include "KeyEventHandlingPolicy.hpp"

void KeyEventHandlingPolicy::handleKeyDownEvent(SDL_keysym* keysym) const {
  switch (keysym->sym) {
    case SDLK_ESCAPE:
      ::SDL_Quit();
      ::exit(0);
      break;
    default:
      break;
  }
}
