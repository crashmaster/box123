#include <SDLVideoInitPolicy.hpp>

int SDLVideoInitPolicy::SDL_Init() const {
  return ::SDL_Init(SDL_INIT_VIDEO);
}

const SDL_VideoInfo* SDLVideoInitPolicy::SDL_GetVideoInfo() const {
  return ::SDL_GetVideoInfo();
}

int SDLVideoInitPolicy::SDL_GL_SetAttributes() const {

}

Uint32 SDLVideoInitPolicy::SDL_GetVideoModeFlags() const {

}

SDL_Surface* SDLVideoInitPolicy::SDL_SetVideoMode(int, int, int, Uint32) const {

}

void SDLVideoInitPolicy::handleError() const {
  ::SDL_Quit();
  ::exit(1);
}
