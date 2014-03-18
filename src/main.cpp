#include <iostream>

#include "Globals.hpp"

#include "GameView.hpp"
#include "MenuView.hpp"
#include "StartView.hpp"
#include "EndView.hpp"
#include "GameController.hpp"
#include "MenuController.hpp"

#include "Game.hpp"

#include <SFML/Graphics.hpp>

int main ()
{
  globals.init();

  Game game(140, 124, 20, 10, 50);
  GameController gameController(&game);
  GameView gameView(&gameController, &game, globals.getWindow());

  MenuController menuController(&game);
  MenuView menuView(&menuController, globals.getWindow());
  EndView endView(&gameController, globals.getWindow());
  StartView startView(&gameController, globals.getWindow());

  globals.addView("Game", &gameView);
  globals.addView("Menu", &menuView);
  globals.addView("End", &endView);
  globals.addView("Start", &startView);

  globals.setCurrentView("Start");
  globals.gameLoop();

  return 0;
}
