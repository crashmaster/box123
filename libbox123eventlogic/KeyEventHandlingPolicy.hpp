#ifndef __KEY_EVENT_HANDLING_POLICY_HPP__
#define __KEY_EVENT_HANDLING_POLICY_HPP__

#include <SDL/SDL.h>

class KeyEventHandlingPolicy {
  protected:
    bool handleKeyDownEvent(SDL_keysym* keysym) const;
};

#endif
