#ifndef INCLUDED_COUNTERCONDITION_H
#define INCLUDED_COUNTERCONDITION_H

#include "Condition.hpp"

class CounterCondition: public Condition
{
public:
	CounterCondition (unsigned int value);
	virtual ~CounterCondition ();

	virtual void step();
	virtual void reset(int value);

	virtual operator std::string() const;

private:
	unsigned int counter;
};


#endif /* INCLUDED_COUNTERCONDITION_H */
