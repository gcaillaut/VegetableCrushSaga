#ifndef INCLUDED_BASICITEM_HPP
#define INCLUDED_BASICITEM_HPP

#include "Item.hpp"

class Board;

///
/// \brief Item basique
/// \see Item
///
class BasicItem : public Item
{
  public:
	BasicItem(const std::string &name, const unsigned int points);
	virtual ~BasicItem ();

	virtual void create_callback(Board & board, unsigned int pos);
	virtual void destroy_callback(Board & board, unsigned int pos);
};

#endif /* INCLUDED_BASICITEM_HPP */
