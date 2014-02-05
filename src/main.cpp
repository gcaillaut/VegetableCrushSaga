#include <iostream>

#include "Graphic.hpp"
#include "GraphicView.hpp"
#include "GraphicController.hpp"
#include "Game.hpp"

int main ()
{
  game.init();

  Graphic graphic(140, 124, 20, 10, 50);
  GraphicController graphicController(&graphic);
  GraphicView graphicView(&graphicController, &graphic, game.getWindow());

  sf::Clock clock;
  float fps = 0;

  while (graphicView.isRunning())
    {
	  fps = 1.f / clock.getElapsedTime().asSeconds();
	  game.getWindow().setTitle("[FPS: " + std::to_string(fps) + "]");
	  clock.restart();

      graphicView.sendEvents();

      graphicView.clear();
      graphicView.draw();
      graphicView.display();
    }

  return 0;
}
