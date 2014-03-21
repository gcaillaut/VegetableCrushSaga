#ifndef INCLUDED_ITEMGENERATOR_H
#define INCLUDED_ITEMGENERATOR_H

#include <stack>

class Item;

#include "utils/Factory.hpp"

class ItemGenerator
{
public:
	ItemGenerator ();
	virtual ~ItemGenerator ();

	virtual std::unique_ptr<Item> generate () = 0;
	void forceGenerationOf (const std::string& key);
	void registerItem (const std::string& key);

	void generateSpecial(bool b);

protected:
	bool generate_special;

	Factory<Item> factory;
	std::vector<std::string> registered_items;
	std::stack<std::string> forced_items;
};


#endif /* INCLUDED_ITEMGENERATOR_H */
