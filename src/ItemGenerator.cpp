#include "ItemGenerator.hpp"

#include "Globals.hpp"

ItemGenerator::ItemGenerator ()
{
	factory = globals.getItemFactory();
}

ItemGenerator::~ItemGenerator ()
{

}

void ItemGenerator::forceGenerationOf (const std::string& key)
{
	forced_items.push(key);
}

void ItemGenerator::registerItem (const std::string& key)
{
	registered_items.push_back(key);
}
