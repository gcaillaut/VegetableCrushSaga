#include "Board.hpp"
#include "Item.hpp"

Board::Board (unsigned int width, unsigned int height) :
  width(width),
  height(height),
  items(width * height)
{}

Board::~Board ()
{}
