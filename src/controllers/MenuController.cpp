#include "controllers/MenuController.hpp"
#include "models/Game.hpp"

#include "Globals.hpp"

MenuController::MenuController(Game *game): Controller(), game(game)
{
}

MenuController::~MenuController()
{
}

void MenuController::onClick(const float x, const float y)
{
}

void MenuController::onClickRelease(const float x, const float y)
{
}

void MenuController::onLostFocus()
{
  game->setActive(false);
}

void MenuController::onGainedFocus()
{
  game->setActive(true);
}

void MenuController::onRetour()
{
  globals.setCurrentView("Game");
}

void MenuController::onQuitter()
{
  globals.shutdown();
}
