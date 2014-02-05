#ifndef INCLUDED_ITEM_HPP
#define INCLUDED_ITEM_HPP

#include <string>

#include <SFML/Graphics/Sprite.hpp>

class Board;

class Item : public sf::Sprite
{
  public:
	Item(std::string name);
	virtual ~Item ();

	virtual void update(Board & board, sf::Vector2f pos) = 0;

	void goTo (const sf::Vector2f & pos);
	std::string getName () const;

	void destroy ();
	void repair () {destroyed = false;}

	bool isDestroyed () const;
	bool isMoving() const;

	bool operator==(const Item& item) const;
	bool operator!=(const Item& item) const;

  private:
	const std::string name;

	bool destroyed;
	bool moving;
};

#endif /* INCLUDED_ITEM_HPP */
