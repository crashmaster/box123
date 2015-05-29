#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <SDL2/SDL.h>

#include <boost/noncopyable.hpp>


template <typename EventProcessingPolicy,
          typename DrawScenePolicy>
class Scene: private EventProcessingPolicy,
             private DrawScenePolicy,
             private boost::noncopyable {
  public:
    bool step(SDL_Window* window) const {
      bool proceed = false;
      if ((proceed = EventProcessingPolicy::handleEvents()) == true) {
        DrawScenePolicy::drawScene(window);
      }
      return proceed;
    }
};

#endif
