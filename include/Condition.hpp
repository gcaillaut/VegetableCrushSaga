#ifndef INCLUDED_CONDITION_H
#define INCLUDED_CONDITION_H

class Condition
{
public:
	Condition ();
	virtual ~Condition ();

	virtual void step() = 0;
	operator bool() const;
	
protected:
	bool state;
};


#endif /* INCLUDED_CONDITION_H */
