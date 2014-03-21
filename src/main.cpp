#include "Globals.hpp"

#include "views/GameView.hpp"
#include "views/MenuView.hpp"
#include "views/StartView.hpp"
#include "views/EndView.hpp"

#include "controllers/GameController.hpp"
#include "controllers/MenuController.hpp"
#include "controllers/EndController.hpp"

#include "models/Game.hpp"

int main ()
{
  globals.init();
  bool first_time = true;

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

	globals.setCurrentView(first_time ? "Start" : "Game");
	globals.gameLoop();

	first_time = false;

	globals.clearViews();
  }

  return 0;
}
