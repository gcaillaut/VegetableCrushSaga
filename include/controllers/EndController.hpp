#ifndef END_CONTROLLER_HPP
#define END_CONTROLLER_HPP

#include "Controller.hpp"

class Game;

class EndController: public Controller
{
  public:
	EndController();
	virtual ~EndController();

	virtual void onClick (const float x, const float y);
	virtual void onClickRelease (const float x, const float y);
	virtual void onLostFocus ();
	virtual void onGainedFocus ();

	void onRecommencer();
	void onQuitter();
};

#endif // END_CONTROLLER_HPP
