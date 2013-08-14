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
    void step() const {
      EventProcessingPolicy::handleEvents();
      DrawScenePolicy::drawScene();
    }
};

#endif
