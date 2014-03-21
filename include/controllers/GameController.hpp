#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "Controller.hpp"

class Game;

class GameController: public Controller
{
  public:
	GameController (Game *game);
	virtual ~GameController ();

	virtual void onClick (const float x, const float y);
	virtual void onClickRelease (const float x, const float y);
	virtual void onLostFocus ();
	virtual void onGainedFocus ();

	void onEscape();
	void onQuit();

  private:
	Game *game;
};

#endif // GAME_CONTROLLER_HPP
