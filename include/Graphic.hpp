#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include <memory>
#include <stack>

#include <SFML/Graphics/RectangleShape.hpp>
#include "Board.hpp"
//class Board;

class Graphic
{
public:
  Graphic(unsigned int width, unsigned int height, unsigned int cell_size);
  virtual ~Graphic();

  void setClickPosition(const float x, const float y);
  void setReleasePosition(const float x, const float y);

  void executeMovement();
  void updateGame();

  void setActive (bool value);

  Board& getBoard ();
  bool isActive ();

private:
  Board board;

  unsigned int first_item;
  unsigned int second_item;

  bool first_selected;
  bool second_selected;

  std::stack<sf::Vector2u> move_registered;

  bool active_input;

  void registerMove(unsigned int source, unsigned int target);
};

#endif // GRAPHIC_HPP
