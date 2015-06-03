#ifndef __VIDEO_SURFACE_HPP__
#define __VIDEO_SURFACE_HPP__

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include <boost/noncopyable.hpp>


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

    SDL_Window* init() {
      SDL_Window* window = nullptr;
      if (nullptr == (window = SDLVideoInitPolicy::initSDL(_width, _height))) {
        return nullptr;
      }

      OpenGLInitPolicy::initOpenGL(_width, _height);

      return window;
    }

  private:
    int _width;
    int _height;
};

#endif
