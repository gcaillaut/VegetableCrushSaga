#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <stack>

#include <SFML/Graphics/RectangleShape.hpp>
#include "Board.hpp"

class Game
{
  public:
	Game(unsigned int x, unsigned int y, unsigned int width, unsigned int height,
			unsigned int cell_size);
	virtual ~Game();

	void setClickPosition(const float x, const float y);
	void setReleasePosition(const float x, const float y);

	void executeMovement();
	void updateGame();

	void setActive (bool value);

	Board& getBoard ();
	bool isActive ();

  private:
	Board board;

	sf::Vector2u first_item;
	sf::Vector2u second_item;

	bool first_selected;
	bool second_selected;

	std::stack<sf::Vector2u> move_registered;

	bool active_input;

	void registerMove(unsigned int source, unsigned int target);
};

#endif // GAME_HPP
