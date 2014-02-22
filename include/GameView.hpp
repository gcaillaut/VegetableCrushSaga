#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include "View.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Game;

class GameView: public View
{
	public:
		GameView (Controller *controller, Game *game, sf::RenderWindow& window);
		virtual ~GameView();

		virtual void clear ();
		virtual void draw ();
		virtual void display ();

		virtual void sendEvents ();

		bool isRunning() const;

		void loop();

	private:
		Game *game;
		sf::RenderWindow& window;

		bool running;
};

#endif // GAME_VIEW_HPP
