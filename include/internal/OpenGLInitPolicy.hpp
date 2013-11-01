#ifndef __OPEN_GL_INIT_POLICY_HPP__
#define __OPEN_GL_INIT_POLICY_HPP__

#include <GL/gl.h>
#include <GL/glu.h>

template <typename LoggingPolicy>
class OpenGLInitPolicy: private LoggingPolicy {
  protected:
    void initOpenGL(const int width, const int height) const {
      LoggingPolicy::log("OpenGL initialization started.");

      glShadeModel(GL_SMOOTH);
      glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      glClearDepth(1.0f);
      glEnable(GL_DEPTH_TEST);
      glDepthFunc(GL_LEQUAL);
      glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

      glViewport(0, 0, width, height);
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      float ratio = (float) width / (float) height;
      gluPerspective(45.0f, ratio, 0.1f, 100.0f);
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

      LoggingPolicy::log("OpenGL initialization finished.");
    }
};

#endif
