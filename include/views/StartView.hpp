#ifndef START_VIEW_HPP
#define START_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "View.hpp"

class Game;

class StartView: public View
{
  public:
	StartView (Controller *controller, sf::RenderWindow& window);
	virtual ~StartView();

	virtual void clear ();
	virtual void draw ();
	virtual void display ();

	virtual void sendEvents ();

	virtual void loop();

  private:
	sf::RenderWindow& window;

	sf::Clock start_clock;
	sf::Text start_text;
};

#endif // END_VIEW_HPP
