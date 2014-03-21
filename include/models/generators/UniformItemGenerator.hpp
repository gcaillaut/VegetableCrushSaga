#ifndef INCLUDED_UNIFORMITEMGENERATOR_H
#define INCLUDED_UNIFORMITEMGENERATOR_H

#include <chrono>

#include "ItemGenerator.hpp"

///
/// \brief Générateur uniforme d'item
/// Chaque item a la même chance d'être généré
///
/// \see ItemGenerator
///
class UniformItemGenerator : public ItemGenerator
{
public:
	UniformItemGenerator ();
	virtual ~UniformItemGenerator ();

	virtual std::unique_ptr<Item> generate ();

	///
	/// \brief Renvoie un identifiant aléatoire
	/// \return Identifiant
	///
	std::string getRandomItemKey ();

private:
	std::minstd_rand0 generator;
};


#endif /* INCLUDED_UNIFORMITEMGENERATOR_H */
