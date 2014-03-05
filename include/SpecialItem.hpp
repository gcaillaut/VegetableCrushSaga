#ifndef INCLUDED_SPECIALITEM_HPP
#define INCLUDED_SPECIALITEM_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
 
#include "Item.hpp"

class Board;

class SpecialItem : public Item
{
public:
	SpecialItem(const std::string &name, const unsigned int points);
	virtual ~SpecialItem ();

	virtual void create_callback(Board & board, unsigned int pos);
	virtual void destroy_callback(Board & board, unsigned int pos);
 	virtual SpecialItem* clone();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Sprite overlay;
};

#endif /* INCLUDED_SPECIALITEM_HPP */
