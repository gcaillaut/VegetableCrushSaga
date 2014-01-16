#ifndef TESTCONTROLLER_HPP
#define TESTCONTROLLER_HPP

#include "Controller.hpp"

class TestController: public Controller
{
public:
  TestController(View* view, Test* model): Controller("Test", view), model(model) {}
  virtual ~TestController() {}

  virtual void manageEvent(const sf::Event event)
  {
    if (event.type == sf::Event::MouseButtonPressed)
      {
        model->addRectangle(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
      }

    if (event.type == sf::Event::Closed)
      {
        game.getWindow().close();
      }
  }
  
private:
  Test* model;

};

#endif
