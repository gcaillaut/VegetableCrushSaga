#ifndef INCLUDED_UNIFORMITEMGENERATOR_H
#define INCLUDED_UNIFORMITEMGENERATOR_H

#include <chrono>

#include "ItemGenerator.hpp"

class UniformItemGenerator : public ItemGenerator
{
public:
	UniformItemGenerator ();
	virtual ~UniformItemGenerator ();

	virtual std::unique_ptr<Item> generate ();

	std::string getRandomItemKey ();

private:
	std::minstd_rand0 generator;
};


#endif /* INCLUDED_UNIFORMITEMGENERATOR_H */
