#ifndef __SDL_VIDEO_INIT_POLICY_HPP__
#define __SDL_VIDEO_INIT_POLICY_HPP__

#include <SDL/SDL.h>
#include <string>

class SDLVideoInitPolicy {
  protected:
    int SDL_Init() const;
    const SDL_VideoInfo* SDL_GetVideoInfo() const;
    int SDL_GL_SetAttributes() const;
    Uint32 SDL_GetVideoModeFlags() const;
    SDL_Surface* SDL_SetVideoMode(int, int, int, Uint32) const;
    std::string SDL_GetError() const;
    void handleError() const;
};

#endif
