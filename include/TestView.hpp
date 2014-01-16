#ifndef TESTVIEW_HPP
#define TESTVIEW_HPP

#include "Test.hpp"
#include "View.hpp"
#include "Game.hpp"

class TestView: public View
{
public:
  TestView(Test* model, std::string name): View(name), model(model) {}
  virtual ~TestView() {}

  virtual void draw()
  {
    auto& rectangles = model->getRectangles();

    std::for_each(rectangles.begin(), rectangles.end(), [](std::unique_ptr<sf::RectangleShape>& p){
        game.getWindow().draw(*(p.get())); 
      }); 

    game.getWindow().display();
  }

private:
  Test* model;

};

#endif
