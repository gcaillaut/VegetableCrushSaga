#ifndef INCLUDED_COUNTERCONDITION_H
#define INCLUDED_COUNTERCONDITION_H

#include "Condition.hpp"

///
/// \brief Condition de fin de jeu basée sur un nombre de coups
///
class CounterCondition: public Condition
{
public:
	///
	/// \brief Constructeur de la condition
	/// \param value Valeur de départ
	///
	CounterCondition (unsigned int value);
	virtual ~CounterCondition ();

	virtual void step();
	virtual void reset(int value);

	virtual operator std::string() const;

private:
	unsigned int counter;
};


#endif /* INCLUDED_COUNTERCONDITION_H */
