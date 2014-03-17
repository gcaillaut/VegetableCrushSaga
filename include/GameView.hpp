#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include "View.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

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

		virtual void loop();

		void showComboText();
 
	private:
		Game *game;
		sf::RenderWindow& window;

		sf::Clock combo_clock;
		sf::Text popup_text;
		bool combo_mode;

		sf::Text points_text;
		sf::Text combo_text;
		sf::Text counter_text;
 
		sf::Sprite grass_sprite;

		void initializeGUI();
};

#endif // GAME_VIEW_HPP
