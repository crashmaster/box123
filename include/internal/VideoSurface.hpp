#ifndef __VIDEO_SURFACE_HPP__
#define __VIDEO_SURFACE_HPP__

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "noncopyable.hpp"

template <typename SDLVideoInitPolicy,
          typename OpenGLInitPolicy>
class VideoSurface: private SDLVideoInitPolicy,
                    private OpenGLInitPolicy,
                    private boost::noncopyable {
  public:
    VideoSurface(const int w, const int h): _width(w), _height(h) {
    }

    ~VideoSurface() {
    }

    bool init() {
      if (!SDLVideoInitPolicy::initSDL(_width, _height)) {
        return false;
      }

      OpenGLInitPolicy::initOpenGL(_width, _height);

      return true;
    }

  private:
    int _width;
    int _height;
};

#endif
