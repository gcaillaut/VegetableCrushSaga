#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Text.hpp>

#include "View.hpp"

class Game;

///
/// \brief Vue du jeu
/// \see View
///
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
		void showLevelupText();
 
	private:
		Game *game;
		sf::RenderWindow& window;

		sf::Clock combo_clock;
		sf::Text popup_text;
		bool combo_mode;

		sf::Clock levelup_clock;
		sf::Text levelup_text;
		bool levelup_mode;

		sf::Text points_text;
		sf::Text combo_text;
		sf::Text counter_text;
		sf::Text level_text;

		sf::Sprite grass_sprite;

		void initializeGUI();
};

#endif // GAME_VIEW_HPP
