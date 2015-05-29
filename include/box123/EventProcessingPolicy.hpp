#ifndef __EVENT_PROCESSING_POLICY_HPP__
#define __EVENT_PROCESSING_POLICY_HPP__

#include <SDL/SDL.h>

template <typename SDLEventHandlingPolicy,
          typename KeyEventHandlingPolicy>
class EventProcessingPolicy: private SDLEventHandlingPolicy,
                             private KeyEventHandlingPolicy {
  protected:
    bool handleEvents() const {
      SDL_Event event;

      bool proceed = true;
      while (proceed && SDLEventHandlingPolicy::SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_KEYDOWN:
            proceed = KeyEventHandlingPolicy::handleKeyDownEvent(&event.key.keysym);
            break;
          case SDL_QUIT:
            proceed = SDLEventHandlingPolicy::handleQuit();
            break;
        }
      }

      return proceed;
    }
};

#endif
