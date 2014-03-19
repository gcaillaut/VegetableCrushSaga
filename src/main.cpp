#include <iostream>

#include "Globals.hpp"

#include "GameView.hpp"
#include "MenuView.hpp"
#include "StartView.hpp"
#include "EndView.hpp"
#include "GameController.hpp"
#include "MenuController.hpp"
#include "EndController.hpp"

#include "Game.hpp"

#include <SFML/Graphics.hpp>

int main ()
{
  globals.init();

  while (globals.isRetrying())
  {
	globals.setRetry(false);
	globals.activate();

	Game game(140, 124, 20, 10, 50);

	GameController gameController(&game);
	MenuController menuController(&game);
	EndController endController;

	GameView gameView(&gameController, &game, globals.getWindow());
	MenuView menuView(&menuController, globals.getWindow());
	EndView endView(&endController, globals.getWindow());
	StartView startView(&gameController, globals.getWindow());

	globals.addView("Game", &gameView);
	globals.addView("Menu", &menuView);
	globals.addView("End", &endView);
	globals.addView("Start", &startView);

	globals.setCurrentView("Start");
	globals.gameLoop();

	globals.clearViews();
  }

  return 0;
}
