#include "CounterCondition.hpp"
#include <string>

CounterCondition::CounterCondition(unsigned int value):
	Condition(),
	counter(value)
{}

CounterCondition::~CounterCondition()
{}

void CounterCondition::step()
{
	if (!state && --counter == 0)
		{
			state = true;	
		}
}

CounterCondition::operator std::string () const
{
	return std::to_string(counter);
}
