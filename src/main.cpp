#include <iostream>

#include "Globals.hpp"

#include "GameView.hpp"
#include "GameController.hpp"
#include "Game.hpp"

int main ()
{
  globals.init();

  Game game(140, 124, 20, 10, 50);
  GameController gameController(&game);
  GameView gameView(&gameController, &game, globals.getWindow());

  gameView.loop();

  return 0;
}
