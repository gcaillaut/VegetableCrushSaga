#ifndef END_VIEW_HPP
#define END_VIEW_HPP

#include "View.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <SFML/Graphics/Text.hpp>

#include <SFGUI/SFGUI.hpp>

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

	std::vector<sfg::Button::Ptr> buttons;

	sfg::SFGUI sfgui;
	sfg::Desktop sfgDesktop;
	sfg::Window::Ptr sfgWindow;
	sfg::Box::Ptr box;

	sf::Clock gameover_clock;
	sf::Text gameover_text;


	void updateText();

};

#endif // END_VIEW_HPP
