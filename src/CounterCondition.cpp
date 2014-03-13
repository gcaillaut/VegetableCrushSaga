#include "CounterCondition.hpp"
#include <iostream>

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

	std::cout << "Counter: " << counter << std::endl;
}


