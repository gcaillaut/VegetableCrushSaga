#include <iostream>

#include "Game.hpp"
#include "TestView.hpp"
#include "TestController.hpp"

int main ()
{
  game.init();

  Test test;
  TestView view(&test, "Test");
  TestController controller(&view, &test);

  while (game.getWindow().isOpen())
    {
      view.update();
      view.clear();
      view.draw();
    }

  return 0;
}
