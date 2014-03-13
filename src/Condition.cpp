#include "Condition.hpp"

Condition::Condition():
	state(false)
{}

Condition::~Condition()
{}

Condition::operator bool() const
{
	return state;
}
