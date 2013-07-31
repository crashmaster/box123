#include <boost/test/unit_test.hpp>
#include <Box123VideoSurface.hpp>

BOOST_AUTO_TEST_SUITE(VideoSurfaceTestSuite)

std::vector<std::string> LOGOUTPUT_TESTING;

class LoggingPolicy_Test {
  protected:
    LoggingPolicy_Test() {
      LOGOUTPUT_TESTING.clear();
    }
    void log(const std::string& message) const {
      LOGOUTPUT_TESTING.push_back(message);
    }
};

class SDLVideoInfo_Testing_OK {
  public:
    SDLVideoInfo_Testing_OK(): _pixelFormat(0), _videoInfo(0) {
      _pixelFormat = new SDL_PixelFormat;
      _videoInfo = new SDL_VideoInfo;
      _videoInfo->vfmt = _pixelFormat;
      _pixelFormat->BitsPerPixel = 32;
    }
    ~SDLVideoInfo_Testing_OK() {
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

class SDLVideoInfo_Testing_NOK {
  public:
    SDL_VideoInfo* getVideoInfo() const {
      return 0;
    }
};

class SDLSurface_Testing_OK {
  public:
    SDLSurface_Testing_OK(): _videoSurface(0) {
      _videoSurface = new SDL_Surface;
    }
    ~SDLSurface_Testing_OK() {
      delete _videoSurface;
    }
    SDL_Surface* getVideoSurface() const {
      return _videoSurface;
    }
  private:
    SDL_Surface* _videoSurface;
};

class SDLSurface_Testing_NOK {
  public:
    SDL_Surface* getVideoSurface() const {
      return 0;
    }
};

class SDLVideoInitPolicy_TestingHappyFlow {
  protected:
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
  private:
    SDLVideoInfo_Testing_OK _videoInfo;
    SDLSurface_Testing_OK _videoSurface;
};

class SDLVideoInitPolicy_TestingSDLInitFail: public SDLVideoInitPolicy_TestingHappyFlow {
  protected:
    int SDL_Init() const {
      return -1;
    }
};

class SDLVideoInitPolicy_TestingSDLGetVideoInfoFail: public SDLVideoInitPolicy_TestingHappyFlow {
  protected:
    SDL_VideoInfo* SDL_GetVideoInfo() const {
      return _videoInfo.getVideoInfo();
    }
  private:
    SDLVideoInfo_Testing_NOK _videoInfo;
};

class SDLVideoInitPolicy_TestingSDLGLSetAttributesFail: public SDLVideoInitPolicy_TestingHappyFlow {
  protected:
    int SDL_GL_SetAttributes() const {
      return -1;
    }
};

class SDLVideoInitPolicy_TestingSDLSetVideoModeFail: public SDLVideoInitPolicy_TestingHappyFlow {
  protected:
    SDL_Surface* SDL_SetVideoMode(int, int, int, Uint32) const {
      return _videoSurface.getVideoSurface();
    }
  private:
    SDLSurface_Testing_NOK _videoSurface;
};

bool SDL_QUIT_CALLED = false;
int EXIT_CODE = 0;

class SDLErrorHandlingPolicy_Testing {
  protected:
    SDLErrorHandlingPolicy_Testing() {
      SDL_QUIT_CALLED = false;
      EXIT_CODE = 0;
    }
    void handleError() const {
      SDL_QUIT_CALLED = true;
      EXIT_CODE = 1;
    }
    std::string getError() const {
      return "ERROR XY!";
    }
};

class OpenGLInitPolicy_TestingHappyFlow {
  protected:
    void init(int, int) { }
};

BOOST_AUTO_TEST_CASE(testVideoSurfaceCreate) {
  typedef Box123VideoSurface<LoggingPolicy_Test,
                             SDLVideoInitPolicy_TestingHappyFlow,
                             SDLErrorHandlingPolicy_Testing,
                             OpenGLInitPolicy_TestingHappyFlow> TestVideoSurfaceType;

  TestVideoSurfaceType myVideoSurface(120, 120);
}

BOOST_AUTO_TEST_CASE(testVideoSurfaceXstructorLogging) {
  typedef Box123VideoSurface<LoggingPolicy_Test,
                             SDLVideoInitPolicy_TestingHappyFlow,
                             SDLErrorHandlingPolicy_Testing,
                             OpenGLInitPolicy_TestingHappyFlow> TestVideoSurfaceType;

  TestVideoSurfaceType* myVideoSurface = new TestVideoSurfaceType(240, 240);
  delete myVideoSurface;

  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.size(), std::vector<std::string>::size_type(2));
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(0), "Box123VideoSurface object constructed.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(1), "Box123VideoSurface object destructed.");
}

BOOST_AUTO_TEST_CASE(testVideoSurface_HappyFlow) {
  typedef Box123VideoSurface<LoggingPolicy_Test,
                             SDLVideoInitPolicy_TestingHappyFlow,
                             SDLErrorHandlingPolicy_Testing,
                             OpenGLInitPolicy_TestingHappyFlow> TestVideoSurfaceType;

  TestVideoSurfaceType myVideoSurface(360, 360);
  myVideoSurface.init();

  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.size(), std::vector<std::string>::size_type(7));
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(0), "Box123VideoSurface object constructed.");
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
  typedef Box123VideoSurface<LoggingPolicy_Test,
                             SDLVideoInitPolicy_TestingSDLInitFail,
                             SDLErrorHandlingPolicy_Testing,
                             OpenGLInitPolicy_TestingHappyFlow> TestVideoSurfaceType;

  TestVideoSurfaceType myVideoSurface(480, 480);
  myVideoSurface.init();

  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.size(), std::vector<std::string>::size_type(5));
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(0), "Box123VideoSurface object constructed.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(1), "Video surface initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(2), "SDL video initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(3), "SDL init failed: ERROR XY!");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(4), "SDL video initialization failed.");
  BOOST_CHECK_EQUAL(SDL_QUIT_CALLED, true);
  BOOST_CHECK_EQUAL(EXIT_CODE, 1);
}

BOOST_AUTO_TEST_CASE(testVideoSurface_SDL_GetVideoInfo_NOK) {
  typedef Box123VideoSurface<LoggingPolicy_Test,
                             SDLVideoInitPolicy_TestingSDLGetVideoInfoFail,
                             SDLErrorHandlingPolicy_Testing,
                             OpenGLInitPolicy_TestingHappyFlow> TestVideoSurfaceType;

  TestVideoSurfaceType myVideoSurface(640, 640);
  myVideoSurface.init();

  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.size(), std::vector<std::string>::size_type(5));
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(0), "Box123VideoSurface object constructed.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(1), "Video surface initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(2), "SDL video initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(3), "SDL get video information failed: ERROR XY!");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(4), "SDL video initialization failed.");
  BOOST_CHECK_EQUAL(SDL_QUIT_CALLED, true);
  BOOST_CHECK_EQUAL(EXIT_CODE, 1);
}

BOOST_AUTO_TEST_CASE(testVideoSurface_SDL_GL_SetAttributes_NOK) {
  typedef Box123VideoSurface<LoggingPolicy_Test,
                             SDLVideoInitPolicy_TestingSDLGLSetAttributesFail,
                             SDLErrorHandlingPolicy_Testing,
                             OpenGLInitPolicy_TestingHappyFlow> TestVideoSurfaceType;

  TestVideoSurfaceType myVideoSurface(640, 640);
  myVideoSurface.init();

  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.size(), std::vector<std::string>::size_type(5));
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(0), "Box123VideoSurface object constructed.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(1), "Video surface initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(2), "SDL video initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(3), "SDL set GL attributes failed: ERROR XY!");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(4), "SDL video initialization failed.");
  BOOST_CHECK_EQUAL(SDL_QUIT_CALLED, true);
  BOOST_CHECK_EQUAL(EXIT_CODE, 1);
}

BOOST_AUTO_TEST_CASE(testVideoSurface_SDL_SetVideoMode_NOK) {
  typedef Box123VideoSurface<LoggingPolicy_Test,
                             SDLVideoInitPolicy_TestingSDLSetVideoModeFail,
                             SDLErrorHandlingPolicy_Testing,
                             OpenGLInitPolicy_TestingHappyFlow> TestVideoSurfaceType;

  TestVideoSurfaceType myVideoSurface(640, 640);
  myVideoSurface.init();

  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.size(), std::vector<std::string>::size_type(5));
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(0), "Box123VideoSurface object constructed.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(1), "Video surface initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(2), "SDL video initialization started.");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(3), "SDL set video mode failed: ERROR XY!");
  BOOST_CHECK_EQUAL(LOGOUTPUT_TESTING.at(4), "SDL video initialization failed.");
  BOOST_CHECK_EQUAL(SDL_QUIT_CALLED, true);
  BOOST_CHECK_EQUAL(EXIT_CODE, 1);
}

BOOST_AUTO_TEST_SUITE_END()
