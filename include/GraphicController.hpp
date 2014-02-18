#ifndef GRAPHIC_CONTROLLER_HPP
#define GRAPHIC_CONTROLLER_HPP

#include "Controller.hpp"

class Graphic;

class GraphicController: public Controller
{
public:
	GraphicController (Graphic *graphic);
	virtual ~GraphicController ();

	virtual void onClick (const float x, const float y);
	virtual void onClickRelease (const float x, const float y);
	virtual void onLostFocus ();
	virtual void onGainedFocus ();
	virtual void onMouseMotion (const float x, const float y);

private:
	Graphic *graphic;
};

#endif // GRAPHIC_CONTROLLER_HPP
