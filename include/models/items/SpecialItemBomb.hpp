#ifndef INCLUDED_SPECIALITEM_HPP
#define INCLUDED_SPECIALITEM_HPP
 
#include "Item.hpp"

class Board;

///
/// \brief Item bombe
/// \see Item
///
class SpecialItemBomb : public Item
{
public:
	SpecialItemBomb(const std::string &name, const unsigned int points);
	virtual ~SpecialItemBomb ();

	virtual void create_callback(Board & board, unsigned int pos);
	virtual void destroy_callback(Board & board, unsigned int pos);

private:
	void explode(Board & board, unsigned pos, unsigned range);
};

#endif /* INCLUDED_SPECIALITEM_HPP */
