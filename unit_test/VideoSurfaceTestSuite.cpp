#include <boost/test/unit_test.hpp>
#include "VideoSurface.hpp"

BOOST_AUTO_TEST_SUITE(VideoSurfaceTestSuite)

static std::vector<std::string> LOGOUTPUT_TESTING;

class LoggingPolicy_Test {
  protected:
    LoggingPolicy_Test() {
      LOGOUTPUT_TESTING.clear();
    }
    void log(const std::string& message) const {
      LOGOUTPUT_TESTING.push_back(message);
    }
};

class SDLVideoInfo_Test_OK {
  public:
    SDLVideoInfo_Test_OK(): _pixelFormat(0), _videoInfo(0) {
      _pixelFormat = new SDL_PixelFormat;
      _videoInfo = new SDL_VideoInfo;
      _videoInfo->vfmt = _pixelFormat;
      _pixelFormat->BitsPerPixel = 32;
    }
    ~SDLVideoInfo_Test_OK() {
      delete _pixelFormat;
      delete _videoInfo;
    }
    SDL_VideoInfo* getVideoInfo() const {
      return _videoInfo;
    }
  private:
    SDL_PixelFormat* _pixelFormat;
    SDL_VideoInfo* _videoInfo;
};

class SDLVideoInfo_Test_NOK {
  public:
    SDL_VideoInfo* getVideoInfo() const {
      return 0;
    }
};

class SDLSurface_Test_OK {
  public:
    SDLSurface_Test_OK(): _videoSurface(0) {
      _videoSurface = new SDL_Surface;
    }
    ~SDLSurface_Test_OK() {
      delete _videoSurface;
    }
    SDL_Surface* getVideoSurface() const {
      return _videoSurface;
    }
  private:
    SDL_Surface* _videoSurface;
};

class SDLSurface_Test_NOK {
  public:
    SDL_Surface* getVideoSurface() const {
      return 0;
    }
};

static bool SDL_QUIT_CALLED = false;
static int EXIT_CODE = 0;

class SDLVideoInitPolicy_TestHappyFlow {
  protected:
    SDLVideoInitPolicy_TestHappyFlow() {
      SDL_QUIT_CALLED = false;
      EXIT_CODE = 0;
    }
    int SDL_Init() const {
      return 0;
    }
    SDL_VideoInfo* SDL_GetVideoInfo() const {
      return _videoInfo.getVideoInfo();
    }
    int SDL_GL_SetAttributes() const {
      return 0;
    }
    Uint32 SDL_GetVideoModeFlags() const {
      return 0;
    }
    SDL_Surface* SDL_SetVideoMode(int, int, int, Uint32) const {
      return _videoSurface.getVideoSurface();
    }
    void handleError() const {
      SDL_QUIT_CALLED = true;
      EXIT_CODE = 1;
    }
    std::string SDL_GetError() const {
      return "ERROR XY!";
    }
  private:
    SDLVideoInfo_Test_OK _videoInfo;
    SDLSurface_Test_OK _videoSurface;
};

class SDLVideoInitPolicy_TestSDLInitFail: public SDLVideoInitPolicy_TestHappyFlow {
  protected:
    int SDL_Init() const {
      return -1;
    }
};

class SDLVideoInitPolicy_TestSDLGetVideoInfoFail: public SDLVideoInitPolicy_TestHappyFlow {
  protected:
    SDL_VideoInfo* SDL_GetVideoInfo() const {
      return _videoInfo.getVideoInfo();
    }
  private:
    SDLVideoInfo_Test_NOK _videoInfo;
};

class SDLVideoInitPolicy_TestSDLGLSetAttributesFail: public SDLVideoInitPolicy_TestHappyFlow {
  protected:
    int SDL_GL_SetAttributes() const {
      return -1;
    }
};

class SDLVideoInitPolicy_TestSDLSetVideoModeFail: public SDLVideoInitPolicy_TestHappyFlow {
  protected:
    SDL_Surface* SDL_SetVideoMode(int, int, int, Uint32) const {
      return _videoSurface.getVideoSurface();
    }
  private:
    SDLSurface_Test_NOK _videoSurface;
};

class SDLErrorHandlingPolicy_Test {
  protected:
};

class OpenGLInitPolicy_TestHappyFlow {
  protected:
    void init(int, int) { }
};

BOOST_AUTO_TEST_CASE(testVideoSurfaceXstructorLogging) {
  typedef VideoSurface<LoggingPolicy_Test,
                       SDLVideoInitPolicy_TestHappyFlow,
                       OpenGLInitPolicy_TestHappyFlow> TestVideoSurfaceType;

  TestVideoSurfaceType* myTestVideoSurface = new TestVideoSurfaceType(240, 240);
  delete myTestVideoSurface;

  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.size(), std::vector<std::string>::size_type(2));
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(0), "VideoSurface object constructed.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(1), "VideoSurface object destructed.");
}

BOOST_AUTO_TEST_CASE(testVideoSurface_HappyFlow) {
  typedef VideoSurface<LoggingPolicy_Test,
                       SDLVideoInitPolicy_TestHappyFlow,
                       OpenGLInitPolicy_TestHappyFlow> TestVideoSurfaceType;

  TestVideoSurfaceType myTestVideoSurface(360, 360);
  myTestVideoSurface.init();

  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.size(), std::vector<std::string>::size_type(7));
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(0), "VideoSurface object constructed.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(1), "Video surface initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(2), "SDL video initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(3), "SDL video initialization finished.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(4), "OpenGL initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(5), "OpenGL initialization finished.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(6), "Video surface initialization finished.");
  BOOST_CHECK_EQUAL(SDL_QUIT_CALLED, false);
  BOOST_CHECK_EQUAL(EXIT_CODE, 0);
}

BOOST_AUTO_TEST_CASE(testVideoSurface_SDL_Init_NOK) {
  typedef VideoSurface<LoggingPolicy_Test,
                       SDLVideoInitPolicy_TestSDLInitFail,
                       OpenGLInitPolicy_TestHappyFlow> TestVideoSurfaceType;

  TestVideoSurfaceType myTestVideoSurface(480, 480);
  myTestVideoSurface.init();

  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.size(), std::vector<std::string>::size_type(5));
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(0), "VideoSurface object constructed.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(1), "Video surface initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(2), "SDL video initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(3), "SDL init failed: ERROR XY!");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(4), "SDL video initialization failed.");
  BOOST_CHECK_EQUAL(SDL_QUIT_CALLED, true);
  BOOST_CHECK_EQUAL(EXIT_CODE, 1);
}

BOOST_AUTO_TEST_CASE(testVideoSurface_SDL_GetVideoInfo_NOK) {
  typedef VideoSurface<LoggingPolicy_Test,
                       SDLVideoInitPolicy_TestSDLGetVideoInfoFail,
                       OpenGLInitPolicy_TestHappyFlow> TestVideoSurfaceType;

  TestVideoSurfaceType myTestVideoSurface(640, 640);
  myTestVideoSurface.init();

  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.size(), std::vector<std::string>::size_type(5));
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(0), "VideoSurface object constructed.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(1), "Video surface initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(2), "SDL video initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(3), "SDL get video information failed: ERROR XY!");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(4), "SDL video initialization failed.");
  BOOST_CHECK_EQUAL(SDL_QUIT_CALLED, true);
  BOOST_CHECK_EQUAL(EXIT_CODE, 1);
}

BOOST_AUTO_TEST_CASE(testVideoSurface_SDL_GL_SetAttributes_NOK) {
  typedef VideoSurface<LoggingPolicy_Test,
                       SDLVideoInitPolicy_TestSDLGLSetAttributesFail,
                       OpenGLInitPolicy_TestHappyFlow> TestVideoSurfaceType;

  TestVideoSurfaceType myTestVideoSurface(640, 640);
  myTestVideoSurface.init();

  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.size(), std::vector<std::string>::size_type(5));
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(0), "VideoSurface object constructed.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(1), "Video surface initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(2), "SDL video initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(3), "SDL set GL attributes failed: ERROR XY!");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(4), "SDL video initialization failed.");
  BOOST_CHECK_EQUAL(SDL_QUIT_CALLED, true);
  BOOST_CHECK_EQUAL(EXIT_CODE, 1);
}

BOOST_AUTO_TEST_CASE(testVideoSurface_SDL_SetVideoMode_NOK) {
  typedef VideoSurface<LoggingPolicy_Test,
                       SDLVideoInitPolicy_TestSDLSetVideoModeFail,
                       OpenGLInitPolicy_TestHappyFlow> TestVideoSurfaceType;

  TestVideoSurfaceType myTestVideoSurface(640, 640);
  myTestVideoSurface.init();

  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.size(), std::vector<std::string>::size_type(5));
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(0), "VideoSurface object constructed.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(1), "Video surface initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(2), "SDL video initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(3), "SDL set video mode failed: ERROR XY!");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(4), "SDL video initialization failed.");
  BOOST_CHECK_EQUAL(SDL_QUIT_CALLED, true);
  BOOST_CHECK_EQUAL(EXIT_CODE, 1);
}

BOOST_AUTO_TEST_SUITE_END()
