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

		void showComboText();

	private:
		Game *game;
		sf::RenderWindow& window;

		sf::Font font;

		sf::Clock combo_clock;
		sf::Text combo_text;
		bool combo_mode;

		bool running;
};

#endif // GAME_VIEW_HPP
