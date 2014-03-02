#include "GameController.hpp"
#include "Game.hpp"

#include "Globals.hpp"

GameController::GameController(Game *game): Controller(), game(game)
{
}

GameController::~GameController()
{
}

void GameController::onClick(const float x, const float y)
{
  if (game->isActive())
    {
	  game->setClickPosition(x, y);
    }
}

void GameController::onClickRelease(const float x, const float y)
{
  if (game->isActive())
    {
	  game->setReleasePosition(x, y);
	  game->executeMovement();
    }
}

void GameController::onLostFocus()
{

  game->setActive(false);
}

void GameController::onGainedFocus()
{
  game->setActive(true);
}

void GameController::onEscape()
{
  globals.captureScreen();
  globals.setCurrentView("Menu");
}

void GameController::onQuit()
{
  globals.shutdown();
}
