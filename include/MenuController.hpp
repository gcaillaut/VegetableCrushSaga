#ifndef MENU_CONTROLLER_HPP
#define MENU_CONTROLLER_HPP

#include "Controller.hpp"

class Game;

class MenuController: public Controller
{
  public:
	MenuController(Game *game);
	virtual ~MenuController();

	virtual void onClick (const float x, const float y);
	virtual void onClickRelease (const float x, const float y);
	virtual void onLostFocus ();
	virtual void onGainedFocus ();

	void onRetour();
	void onToggleAnimation();
	void onQuitter();

  private:
	Game *game;
};

#endif // MENU_CONTROLLER_HPP
