#ifndef GRAPHIC_VIEW_HPP
#define GRAPHIC_VIEW_HPP

#include "View.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Graphic;

class GraphicView: public View
{
	public:
		GraphicView (Controller *controller, Graphic *graphic, sf::RenderWindow& window);
		virtual ~GraphicView();

		virtual void clear ();
		virtual void draw ();
		virtual void display ();

		virtual void sendEvents ();

		bool isRunning() const;

	private:
		Graphic *graphic;
		sf::RenderWindow& window;

		bool running;
};

#endif // GRAPHIC_VIEW_HPP
