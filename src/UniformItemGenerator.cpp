#include <random>

#include "Item.hpp"
#include "UniformItemGenerator.hpp"

UniformItemGenerator::UniformItemGenerator () : 
	ItemGenerator(),
  generator(std::chrono::system_clock::now().time_since_epoch().count())
{
	forceGenerationOf("CarrotSpecial");
}

UniformItemGenerator::~UniformItemGenerator ()
{}

std::unique_ptr<Item> UniformItemGenerator::generate () 
{
	std::unique_ptr<Item> new_item;

	if (forced_items.empty())
		{
			new_item = std::move(factory.createObject(getRandomItemKey()));
		}
	else
		{
			new_item = std::move(factory.createObject(forced_items.top()));
			forced_items.pop();
		}

	return new_item;
}

std::string UniformItemGenerator::getRandomItemKey ()
{
	unsigned i(generator() % registered_items.size());
	return registered_items.at(i);
}
