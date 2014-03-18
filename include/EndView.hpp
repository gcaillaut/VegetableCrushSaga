#ifndef END_VIEW_HPP
#define END_VIEW_HPP

#include "View.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <SFML/Graphics/Text.hpp>

class Game;

class EndView: public View
{
  public:
	EndView (Controller *controller, sf::RenderWindow& window);
	virtual ~EndView();

	virtual void clear ();
	virtual void draw ();
	virtual void display ();

	virtual void sendEvents ();

	virtual void loop();

  private:
	sf::RenderWindow& window;
	sf::RectangleShape rectangle;

	sf::Clock gameover_clock;
	sf::Text gameover_text;

	void updateText();

};

#endif // END_VIEW_HPP
