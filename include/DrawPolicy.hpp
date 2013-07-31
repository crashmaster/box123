#ifndef __DRAW_POLICY_HPP__
#define __DRAW_POLICY_HPP__

#include <SDL/SDL.h>
#include <GL/gl.h>

class DrawPolicy {
  protected:
    void drawScene() const {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      SDL_GL_SwapBuffers();
    }
};

#endif
