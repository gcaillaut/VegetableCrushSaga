#ifndef INCLUDED_CONDITION_H
#define INCLUDED_CONDITION_H

#include <string>

class Condition
{
public:
	Condition ();
	virtual ~Condition ();

	virtual void step() = 0;
	virtual void reset(int value) = 0;

	operator bool() const;
	virtual operator std::string() const = 0;
 	
protected:
	bool state;
};


#endif /* INCLUDED_CONDITION_H */
