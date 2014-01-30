#include <iostream>

#include "Graphic.hpp"
#include "GraphicView.hpp"
#include "GraphicController.hpp"
#include "Game.hpp"

int main ()
{
  game.init();

  unsigned int cellSize = 100;

  Graphic graphic(game.getWindow().getSize().x / cellSize, game.getWindow().getSize().y / cellSize, cellSize);
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
