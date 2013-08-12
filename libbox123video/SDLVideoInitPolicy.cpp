#include "SDLVideoInitPolicy.hpp"

int SDLVideoInitPolicy::SDL_Init() const {
  return ::SDL_Init(SDL_INIT_VIDEO);
}

const SDL_VideoInfo* SDLVideoInitPolicy::SDL_GetVideoInfo() const {
  return ::SDL_GetVideoInfo();
}

int SDLVideoInitPolicy::SDL_GL_SetAttributes() const {
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

Uint32 SDLVideoInitPolicy::SDL_GetVideoModeFlags() const {
  return SDL_OPENGL;
}

SDL_Surface* SDLVideoInitPolicy::SDL_SetVideoMode(int width,
                                                  int height,
                                                  int bpp,
                                                  Uint32 flags) const {
  return ::SDL_SetVideoMode(width, height, bpp, flags);
}

std::string SDLVideoInitPolicy::SDL_GetError() const {
  return ::SDL_GetError();
}

void SDLVideoInitPolicy::handleError() const {
  ::SDL_Quit();
  ::exit(1);
}
