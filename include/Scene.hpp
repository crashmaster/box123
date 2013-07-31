#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <boost/noncopyable.hpp>
#include <SDL/SDL.h>

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
