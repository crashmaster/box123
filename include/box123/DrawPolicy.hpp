#ifndef __DRAW_POLICY_HPP__
#define __DRAW_POLICY_HPP__

#include <GL/gl.h>
#include <SDL2/SDL.h>


class DrawPolicy {
  protected:
    void drawScene(SDL_Window* window) const {
      static GLfloat rtri = 0.0f;

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glLoadIdentity();
      glTranslatef(0.0f, 0.0f, -6.0f);

      glRotatef(rtri, 0.0f, 1.0f, 0.0f);

      glBegin(GL_TRIANGLES);
      glColor3f(  1.0f,  0.0f,  0.0f);
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glColor3f(  0.0f,  1.0f,  0.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glColor3f(  0.0f,  0.0f,  1.0f);
      glVertex3f( 1.0f, -1.0f,  1.0f);

      glColor3f(  1.0f,  0.0f,  0.0f);
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glColor3f(  0.0f,  0.0f,  1.0f);
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glColor3f(  0.0f,  1.0f,  0.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

      glColor3f(  1.0f,  0.0f,  0.0f);
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glColor3f(  0.0f,  1.0f,  0.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glColor3f(  0.0f,  0.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);

      glColor3f(  1.0f,  0.0f,  0.0f);
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glColor3f(  0.0f,  0.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glColor3f(  0.0f,  1.0f,  0.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glEnd();

      SDL_GL_SwapWindow(window);

      rtri  += 0.02f;
    }
};

#endif
