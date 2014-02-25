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

	void addPoints(unsigned int value);
	void setCombo(unsigned int combo);

	void setActive (bool value);

	Board& getBoard ();
	unsigned int getScore() const;
	unsigned int getCombo() const;

	bool isActive ();

	std::stack<sf::Vector2u> move_registered;

  private:
	Board board;

	sf::Vector2u first_item;
	sf::Vector2u second_item;

	bool first_selected;
	bool second_selected;

	bool active_input;

	unsigned int score;
	unsigned int combo;

	void registerMove(unsigned int source, unsigned int target);
};

#endif // GAME_HPP
