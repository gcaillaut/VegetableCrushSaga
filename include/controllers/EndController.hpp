#ifndef END_CONTROLLER_HPP
#define END_CONTROLLER_HPP

#include "Controller.hpp"

class Game;

///
/// \brief Contrôleur de fin de jeu
/// \see Controller
///
class EndController: public Controller
{
  public:
	EndController();
	virtual ~EndController();

	virtual void onClick (const float x, const float y);
	virtual void onClickRelease (const float x, const float y);
	virtual void onLostFocus ();
	virtual void onGainedFocus ();

	///
	/// \brief Lorsqu'on choisit de recommencer le jeu
	///
	void onRecommencer();

	///
	/// \brief Lorsqu'on quitte le jeu
	///
	void onQuitter();
};

#endif // END_CONTROLLER_HPP
