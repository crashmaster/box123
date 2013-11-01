#ifndef __SDL_VIDEO_INIT_POLICY_HPP__
#define __SDL_VIDEO_INIT_POLICY_HPP__

#include <stdlib.h>
#include <string>
#include <SDL/SDL.h>

template <typename LoggingPolicy>
class SDLVideoInitPolicy: private LoggingPolicy {
  protected:
    bool initSDL(const int width, const int height) {
      LoggingPolicy::log("SDL video initialization started.");

      if (0 != SDL_Init()) {
        LoggingPolicy::log("SDL init failed: " + SDLVideoInitPolicy::SDL_GetError());
        handleError();
        return false;
      }

      const SDL_VideoInfo* videoInfo = 0;
      if (0 == (videoInfo = SDL_GetVideoInfo())) {
        LoggingPolicy::log("SDL get video information failed: " + SDLVideoInitPolicy::SDL_GetError());
        handleError();
        return false;
      }

      if (0 != SDL_GL_SetAttributes()) {
        LoggingPolicy::log("SDL set GL attributes failed: " + SDLVideoInitPolicy::SDL_GetError());
        handleError();
        return false;
      }

      int bpp = videoInfo->vfmt->BitsPerPixel;
      Uint32 flags = SDL_GetVideoModeFlags();

      const SDL_Surface* surface = 0;
      if (0 == (surface = SDL_SetVideoMode(width, height, bpp, flags))) {
        LoggingPolicy::log("SDL set video mode failed: " + SDL_GetError());
        handleError();
        return false;
      }

      LoggingPolicy::log("SDL video initialization finished.");
      return true;
    }
  private:
    int SDL_Init() const {
      return ::SDL_Init(SDL_INIT_VIDEO);
    }

    const SDL_VideoInfo* SDL_GetVideoInfo() const {
      return ::SDL_GetVideoInfo();
    }

    int SDL_GL_SetAttributes() const {
      if (0 != ::SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5)) {
        return -1;
      }
      else if (0 != ::SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5)) {
        return -1;
      }
      else if (0 != ::SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5)) {
        return -1;
      }
      else if (0 != ::SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16)) {
        return -1;
      }
      else if (0 != ::SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1)) {
        return -1;
      }
      return 0;
    }

    Uint32 SDL_GetVideoModeFlags() const {
      return SDL_OPENGL;
    }

    SDL_Surface* SDL_SetVideoMode(const int width,
                                  const int height,
                                  const int bpp,
                                  const Uint32 flags) const
    {
      return ::SDL_SetVideoMode(width, height, bpp, flags);
    }

    std::string SDL_GetError() const {
      return ::SDL_GetError();
    }

    void handleError() const {
      ::SDL_Quit();
    }
};

#endif
