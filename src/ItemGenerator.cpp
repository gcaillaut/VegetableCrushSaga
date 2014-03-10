#include "ItemGenerator.hpp"

#include "Globals.hpp"

ItemGenerator::ItemGenerator () :
	generate_special(true),
	registered_items(),
	forced_items()
{
	factory = globals.getItemFactory();
}

ItemGenerator::~ItemGenerator ()
{

}

void ItemGenerator::forceGenerationOf (const std::string& key)
{
	if (generate_special)
		{
			forced_items.push(key);
		}
}

void ItemGenerator::registerItem (const std::string& key)
{
	registered_items.push_back(key);
}

void ItemGenerator::generateSpecial (bool b)
{
	generate_special = b;
}
