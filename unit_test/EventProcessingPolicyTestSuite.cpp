#include "box123/EventProcessingPolicy.hpp"

#include <SDL2/SDL.h>

#include <boost/test/unit_test.hpp>
#include <queue>
#include <vector>

#include "box123/Scene.hpp"


BOOST_AUTO_TEST_SUITE(EventProcessingPolicyTestSuite)

class SDLEventHandlingPolicy_Test {
  protected:
    int SDL_PollEvent(SDL_Event*) const {
      return 0;
    }
};


static std::queue<Uint8> EVENT_QUEUE;
static void clearEVENT_QUEUE() {
  while (!EVENT_QUEUE.empty()) {
    EVENT_QUEUE.pop();
  }
}

static struct EventCounter {
  int SDL_KEYDOWN;
  int SDL_QUIT;
} EVENT_COUNTER;

class SDLEventHandlingPolicy_TestEmptyQueue {
  protected:
    SDLEventHandlingPolicy_TestEmptyQueue() {
      clearEVENT_QUEUE();
    }
    int SDL_PollEvent(SDL_Event* event) const {
      event->type = EVENT_QUEUE.front();
      EVENT_QUEUE.pop();
      return !EVENT_QUEUE.empty();
    }
    void handleQuit() const {
      EVENT_COUNTER.SDL_QUIT += 1;
    }
};

class SDLEventHandlingPolicy_TestKeyDownInQueue: public SDLEventHandlingPolicy_TestEmptyQueue {
  protected:
    SDLEventHandlingPolicy_TestKeyDownInQueue() {
      clearEVENT_QUEUE();
      EVENT_QUEUE.push(SDL_KEYDOWN);
      EVENT_QUEUE.push(SDL_NOEVENT);  // last "event"
    }
};

class SDLEventHandlingPolicy_TestQuitInQueue: public SDLEventHandlingPolicy_TestEmptyQueue {
  protected:
    SDLEventHandlingPolicy_TestQuitInQueue() {
      clearEVENT_QUEUE();
      EVENT_QUEUE.push(SDL_KEYDOWN);
      EVENT_QUEUE.push(SDL_QUIT);
      EVENT_QUEUE.push(SDL_QUIT);
      EVENT_QUEUE.push(SDL_KEYDOWN);
      EVENT_QUEUE.push(SDL_NOEVENT);  // last "event"
    }
};

class SDLEventHandlingPolicy_TestVariousEventsInQueue: public SDLEventHandlingPolicy_TestEmptyQueue {
  protected:
    SDLEventHandlingPolicy_TestVariousEventsInQueue() {
      clearEVENT_QUEUE();
      EVENT_QUEUE.push(SDL_JOYBUTTONUP);
      EVENT_QUEUE.push(SDL_KEYDOWN);
      EVENT_QUEUE.push(SDL_JOYBUTTONDOWN);
      EVENT_QUEUE.push(SDL_KEYUP);
      EVENT_QUEUE.push(SDL_KEYDOWN);
      EVENT_QUEUE.push(SDL_KEYUP);
      EVENT_QUEUE.push(SDL_KEYDOWN);
      EVENT_QUEUE.push(SDL_QUIT);
      EVENT_QUEUE.push(SDL_NOEVENT);  // last "event"
    }
};

class KeyEventHandlingPolicy_Test {
  protected:
    void handleKeyDownEvent(const SDL_keysym*) { }
};

class KeyEventHandlingPolicy_TestKeyDownCapture {
  protected:
    KeyEventHandlingPolicy_TestKeyDownCapture() {
      std::memset(&EVENT_COUNTER, 0, sizeof(EventCounter));
    }
    void handleKeyDownEvent(const SDL_keysym*) const {
      EVENT_COUNTER.SDL_KEYDOWN += 1;
    }
};

class DrawScenePolicy_Test {
  protected:
    void drawScene() const { }
};

BOOST_AUTO_TEST_CASE(testKeyDownEventHandling) {
  typedef EventProcessingPolicy<SDLEventHandlingPolicy_TestKeyDownInQueue,
                                KeyEventHandlingPolicy_TestKeyDownCapture> TestEventProcessingPolicyType;
  typedef Scene<TestEventProcessingPolicyType, DrawScenePolicy_Test> TestSceneType;

  TestSceneType myTestScene;
  myTestScene.step();

  BOOST_CHECK_EQUAL(EVENT_COUNTER.SDL_KEYDOWN, 1);
  BOOST_CHECK_EQUAL(EVENT_COUNTER.SDL_QUIT, 0);
}

BOOST_AUTO_TEST_CASE(testVariousEventHandling) {
  typedef EventProcessingPolicy<SDLEventHandlingPolicy_TestVariousEventsInQueue,
                                KeyEventHandlingPolicy_TestKeyDownCapture> TestEventProcessingPolicyType;
  typedef Scene<TestEventProcessingPolicyType, DrawScenePolicy_Test> TestSceneType;

  TestSceneType myTestScene;
  myTestScene.step();

  BOOST_CHECK_EQUAL(EVENT_COUNTER.SDL_KEYDOWN, 3);
  BOOST_CHECK_EQUAL(EVENT_COUNTER.SDL_QUIT, 1);
}

BOOST_AUTO_TEST_CASE(testQuitEventHandling) {
  typedef EventProcessingPolicy<SDLEventHandlingPolicy_TestQuitInQueue,
                                KeyEventHandlingPolicy_TestKeyDownCapture> TestEventProcessingPolicyType;
  typedef Scene<TestEventProcessingPolicyType, DrawScenePolicy_Test> TestSceneType;

  TestSceneType myTestScene;
  myTestScene.step();

  BOOST_CHECK_EQUAL(EVENT_COUNTER.SDL_KEYDOWN, 1);
  BOOST_CHECK_EQUAL(EVENT_COUNTER.SDL_QUIT, 1);
}

BOOST_AUTO_TEST_SUITE_END()
