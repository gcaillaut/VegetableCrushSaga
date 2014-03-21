#include <string>

#include "models/conditions/CounterCondition.hpp"

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

void CounterCondition::reset(int value)
{
  state = false;
  counter = value;
}

CounterCondition::operator std::string () const
{
  return std::to_string(counter);
}
