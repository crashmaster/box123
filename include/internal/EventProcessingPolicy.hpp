#ifndef __EVENT_PROCESSING_POLICY_HPP__
#define __EVENT_PROCESSING_POLICY_HPP__

#include <SDL/SDL.h>

template <typename SDLEventHandlingPolicy,
          typename KeyEventHandlingPolicy>
class EventProcessingPolicy: private SDLEventHandlingPolicy,
                             private KeyEventHandlingPolicy {
  protected:
    void handleEvents() const {
      SDL_Event event;

      while (SDLEventHandlingPolicy::SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_KEYDOWN:
            KeyEventHandlingPolicy::handleKeyDownEvent(&event.key.keysym);
            break;
          case SDL_QUIT:
            SDLEventHandlingPolicy::handleQuit();
            return;
        }
      }
    }
};

#endif
