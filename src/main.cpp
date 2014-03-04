#include <iostream>

#include "Globals.hpp"

#include "GameView.hpp"
#include "GameController.hpp"
#include "MenuView.hpp"
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
  MenuView menuView(&menuController, &game, globals.getWindow());

  globals.addView("Game", &gameView);
  globals.addView("Menu", &menuView);

  globals.setCurrentView("Game");
  globals.gameLoop();

  return 0;
}
