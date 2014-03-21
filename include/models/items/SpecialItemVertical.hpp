#ifndef INCLUDED_SPECIALITEMVERTICAL_H
#define INCLUDED_SPECIALITEMVERTICAL_H

#include "Item.hpp"

class Board;

///
/// \brief Item spécial vertical
/// \see Item
///
class SpecialItemVertical : public Item
{
public:
	SpecialItemVertical(const std::string &name, const unsigned int points);
	virtual ~SpecialItemVertical ();

	virtual void create_callback(Board & board, unsigned int pos);
	virtual void destroy_callback(Board & board, unsigned int pos);

private:
	void explode(Board & board, unsigned pos, int offset);
};

#endif /* INCLUDED_SPECIALITEMVERTICAL_H */
