#include <OpenGLInitPolicy.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

void OpenGLInitPolicy::init(const int width, const int height) const {
  glShadeModel(GL_SMOOTH);

  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);

  glClearColor(0, 0, 0, 0);

  glViewport(0, 0, width, height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float ratio = (float) width / (float) height;
  gluPerspective(60.0, ratio, 1.0, 1024.0);
}
