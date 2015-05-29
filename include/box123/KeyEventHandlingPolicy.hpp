#ifndef __KEY_EVENT_HANDLING_POLICY_HPP__
#define __KEY_EVENT_HANDLING_POLICY_HPP__

#include <SDL2/SDL.h>


class KeyEventHandlingPolicy {
  protected:
    bool handleKeyDownEvent(SDL_Keysym* keysym) const;
};

#endif
