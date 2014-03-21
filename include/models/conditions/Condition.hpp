#ifndef INCLUDED_CONDITION_H
#define INCLUDED_CONDITION_H

#include <string>

///
/// \brief Condition de fin de jeu de base
///
class Condition
{
public:
	Condition ();
	virtual ~Condition ();

	///
	/// \brief Met à jour la condition
	///
	virtual void step() = 0;

	///
	/// \brief Remet la condition à 'value'
	/// \param value
	///
	virtual void reset(int value) = 0;

	operator bool() const;
	virtual operator std::string() const = 0;
 	
protected:
	bool state;
};


#endif /* INCLUDED_CONDITION_H */
