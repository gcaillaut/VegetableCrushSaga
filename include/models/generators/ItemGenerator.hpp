#ifndef INCLUDED_ITEMGENERATOR_H
#define INCLUDED_ITEMGENERATOR_H

#include <stack>

#include "utils/Factory.hpp"

class Item;

///
/// \brief Générateur d'item de base
///
class ItemGenerator
{
public:
	ItemGenerator ();
	virtual ~ItemGenerator ();

	///
	/// \brief Génère un item
	/// \return Item (std::unique_ptr)
	///
	virtual std::unique_ptr<Item> generate () = 0;

	///
	/// \brief Force la génération de l'item identifié par 'key'
	/// \param key	Identifiant
	///
	void forceGenerationOf (const std::string& key);

	///
	/// \brief Enregistre l'item identifié par 'key' dans le générateur
	/// \param key	Identifiant
	///
	void registerItem (const std::string& key);

	///
	/// \brief Génère des items spéciaux ou non
	/// \param b Oui/Non
	///
	void generateSpecial(bool b);

protected:
	bool generate_special;

	Factory<Item> factory;
	std::vector<std::string> registered_items;
	std::stack<std::string> forced_items;
};


#endif /* INCLUDED_ITEMGENERATOR_H */
