#include <SFML/System/Vector2.hpp>

#include "Globals.hpp"
#include "Board.hpp"
#include "SpecialItem.hpp"

SpecialItem::SpecialItem (const std::string &name, const unsigned int points) :
  Item(name, points)
{
	overlay.setTexture(*globals.getTexturesManager().getRessource("special_item"));
 }

SpecialItem::~SpecialItem ()
{}

void SpecialItem::create_callback (Board& board, unsigned int pos)
{
	Item::create_callback (board, pos);

	unsigned cell_size(board.getCellSize());

	sf::Vector2u texture_size(overlay.getTexture()->getSize());
  overlay.setOrigin(texture_size.x / 2, texture_size.y / 2);
  overlay.setScale(static_cast<float>(cell_size) / texture_size.x,
											 static_cast<float>(cell_size) / texture_size.y);

  overlay.scale(0.4f, 0.4f);
}

void SpecialItem::destroy_callback (Board & board, unsigned int pos)
{
	
}

SpecialItem *SpecialItem::clone()
{
  SpecialItem* item = new SpecialItem(name, value);
  resetItem(item);

  return item;
}

void SpecialItem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// target.draw(*this, states);

	states.transform.translate(getPosition());
	target.draw(overlay, states);
}
