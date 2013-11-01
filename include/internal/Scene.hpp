#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <SDL/SDL.h>
#include "noncopyable.hpp"

template <typename EventProcessingPolicy,
          typename DrawScenePolicy>
class Scene: private EventProcessingPolicy,
             private DrawScenePolicy,
             private boost::noncopyable {
  public:
    bool step() const {
      bool proceed = false;
      if ((proceed = EventProcessingPolicy::handleEvents()) == true) {
        DrawScenePolicy::drawScene();
      }
      return proceed;
    }
};

#endif
