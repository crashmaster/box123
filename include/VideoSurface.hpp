#include <boost/noncopyable.hpp>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

template <typename LogPolicy,
          typename SDLVideoInitPolicy,
          typename OpenGLInitPolicy>
class VideoSurface: private LogPolicy,
                    private SDLVideoInitPolicy,
                    private OpenGLInitPolicy,
                    private boost::noncopyable {
  public:
    VideoSurface(const int w, const int h): _width(w), _height(h) {
      LogPolicy::log("VideoSurface object constructed.");
    }

    ~VideoSurface() {
      LogPolicy::log("VideoSurface object destructed.");
    }

    void init() {
      LogPolicy::log("Video surface initialization started.");

      if (!initSDL()) {
        LogPolicy::log("SDL video initialization failed.");
        return;
      }

      initOpenGL();

      LogPolicy::log("Video surface initialization finished.");
    }

  private:
    bool initSDL() {
      LogPolicy::log("SDL video initialization started.");

      if (0 != SDLVideoInitPolicy::SDL_Init()) {
        LogPolicy::log("SDL init failed: " + SDLVideoInitPolicy::getError());
        SDLVideoInitPolicy::handleError();
        return false;
      }

      const SDL_VideoInfo* videoInfo = 0;
      if (0 == (videoInfo = SDLVideoInitPolicy::SDL_GetVideoInfo())) {
        LogPolicy::log("SDL get video information failed: " + SDLVideoInitPolicy::getError());
        SDLVideoInitPolicy::handleError();
        return false;
      }

      if (0 != SDLVideoInitPolicy::SDL_GL_SetAttributes()) {
        LogPolicy::log("SDL set GL attributes failed: " + SDLVideoInitPolicy::getError());
        SDLVideoInitPolicy::handleError();
        return false;
      }

      int bpp = videoInfo->vfmt->BitsPerPixel;
      Uint32 flags = SDLVideoInitPolicy::SDL_GetVideoModeFlags();

      const SDL_Surface* surface = 0;
      if (0 == (surface = SDLVideoInitPolicy::SDL_SetVideoMode(_width, _height, bpp, flags))) {
        LogPolicy::log("SDL set video mode failed: " + SDLVideoInitPolicy::getError());
        SDLVideoInitPolicy::handleError();
        return false;
      }

      LogPolicy::log("SDL video initialization finished.");
      return true;
    }

    void initOpenGL() {
      LogPolicy::log("OpenGL initialization started.");

      OpenGLInitPolicy::init(_width, _height);

      LogPolicy::log("OpenGL initialization finished.");
    }

    int _width;
    int _height;
};
