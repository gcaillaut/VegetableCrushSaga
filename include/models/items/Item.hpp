#ifndef INCLUDED_ITEM_HPP
#define INCLUDED_ITEM_HPP

#include <string>
#include <memory>

#include <SFML/Graphics/Sprite.hpp>

class Board;

///
/// \brief Item de base
///
class Item : public sf::Sprite
{
public:
	static std::unique_ptr<Item> null_item;

	///
	/// \brief Constructeur d'un item
	/// \param name	  Nom de l'item
	/// \param points Valeur de l'item
	///
	Item(const std::string &name, const unsigned int points);
	virtual ~Item ();

	///
	/// \brief Evènement de création de l'item
	/// \param board  Plateau de jeu
	/// \param pos	  Position de l'item
	///
	virtual void create_callback(Board & board, unsigned int pos);

	///
	/// \brief Evènement de destruction de l'item
	/// \param board  Plateau de jeu
	/// \param pos	  Position de l'item
	///
	virtual void destroy_callback(Board & board, unsigned int pos);

	///
	/// \brief Déplace l'item vers la position 'pos' de façon fluide
	/// \param pos Destination
	///
	void goTo (const sf::Vector2f & pos);

	///
	/// \brief Détruit l'item
	///
	void destroy ();

	///
	/// \brief Définit l'item en état d'échange ou non
	/// \param value Oui/Non
	///
	void setSwap(bool value);

	std::string getName () const;
	unsigned int getValue () const;

	bool isDestroyed () const;
	bool isMoving() const;

	bool operator==(const Item& item) const;
	bool operator!=(const Item& item) const;

  protected:
	const std::string name;

	unsigned int value;

	bool destroyed;
	bool moving;
	bool swapped;
};

#endif /* INCLUDED_ITEM_HPP */
