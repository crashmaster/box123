#ifndef __SDL_EVENT_HANDLING_POLICY_HPP__
#define __SDL_EVENT_HANDLING_POLICY_HPP__

#include <SDL/SDL.h>

class SDLEventHandlingPolicy {
  protected:
    int SDL_PollEvent(SDL_Event* event) const;
    bool handleQuit() const;
};

#endif
