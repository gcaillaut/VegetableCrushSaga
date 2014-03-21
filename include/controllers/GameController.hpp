#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "Controller.hpp"

class Game;

///
/// \brief Contrôleur du jeu
/// \see Controller
///
class GameController: public Controller
{
  public:
	GameController (Game *game);
	virtual ~GameController ();

	virtual void onClick (const float x, const float y);
	virtual void onClickRelease (const float x, const float y);
	virtual void onLostFocus ();
	virtual void onGainedFocus ();

	///
	/// \brief Lorsqu'on appuie sur Echap
	///
	void onEscape();

	///
	/// \brief Lorsqu'on quitte le jeu
	///
	void onQuit();

  private:
	Game *game;
};

#endif // GAME_CONTROLLER_HPP
