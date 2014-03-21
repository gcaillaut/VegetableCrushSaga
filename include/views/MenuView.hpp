#ifndef MENU_VIEW_HPP
#define MENU_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <SFGUI/SFGUI.hpp>

#include "View.hpp"

class Game;

class MenuView: public View
{
	public:
		MenuView (Controller *controller, sf::RenderWindow& window);
		virtual ~MenuView();

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

};

#endif // MENU_VIEW_HPP
