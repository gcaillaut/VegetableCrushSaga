#include <iostream>

#include "Graphic.hpp"
#include "GraphicView.hpp"
#include "GraphicController.hpp"
#include "Game.hpp"

int main ()
{
  game.init();

  Graphic graphic(100, 100, 10, 10, 50);
  GraphicController graphicController(&graphic);
  GraphicView graphicView(&graphicController, &graphic, game.getWindow());

  while (graphicView.isRunning())
    {
      graphicView.sendEvents();

      graphicView.clear();
      graphicView.draw();
      graphicView.display();
    }

  return 0;
}
