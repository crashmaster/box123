#ifndef __SDL_VIDEO_INIT_POLICY_HPP__
#define __SDL_VIDEO_INIT_POLICY_HPP__

#include <stdlib.h>
#include <SDL2/SDL.h>

#include <string>


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

      if (0 != SDL_GL_SetAttributes()) {
        LoggingPolicy::log("SDL set GL attributes failed: " + SDLVideoInitPolicy::SDL_GetError());
        handleError();
        return false;
      }

      SDL_WindowFlags flags = GetWindowFlags();

      const SDL_Window* window = 0;
      if (0 == (window = CreateWindow(width, height, flags))) {
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

    SDL_WindowFlags GetWindowFlags() const {
      return SDL_WINDOW_OPENGL;
    }

    SDL_Window* CreateWindow(const int width,
                             const int height,
                             const SDL_WindowFlags flags) const
    {
      return ::SDL_CreateWindow(
        "box123",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        flags
      );
    }

    std::string SDL_GetError() const {
      return ::SDL_GetError();
    }

    void handleError() const {
      ::SDL_Quit();
    }
};

#endif
