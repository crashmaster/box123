#include <boost/test/unit_test.hpp>
#include "Scene.hpp"

BOOST_AUTO_TEST_SUITE(SceneTestSuite)

static bool HANDLE_EVENTS_CALLED = false;
static bool DRAW_SCENE_CALLED = false;

class EventProcessingPolicy_Test {
  protected:
    EventProcessingPolicy_Test() {
      HANDLE_EVENTS_CALLED = false;
    }
    bool handleEvents() const {
      HANDLE_EVENTS_CALLED = true;
      return true;
    }
};

class DrawScenePolicy_Test {
  protected:
    DrawScenePolicy_Test() {
      DRAW_SCENE_CALLED = false;
    }
    void drawScene() const {
      DRAW_SCENE_CALLED = true;
    }
};

BOOST_AUTO_TEST_CASE(testSceneStep) {
  typedef Scene<EventProcessingPolicy_Test,
                DrawScenePolicy_Test> TestSceneType;

  TestSceneType myTestScene;
  myTestScene.step();
  BOOST_CHECK_EQUAL(HANDLE_EVENTS_CALLED, true);
  BOOST_CHECK_EQUAL(DRAW_SCENE_CALLED, true);
}

BOOST_AUTO_TEST_SUITE_END()
