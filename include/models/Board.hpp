#ifndef INCLUDED_BOARD_HPP
#define INCLUDED_BOARD_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Item;
class Game;

class ItemGenerator;

///
/// \brief Plateau de jeu
///
class Board
{
  public:
	///
	/// \brief Constructeur du plateau
	/// \param x		  Position x du plateau
	/// \param y		  Position y du plateau
	/// \param width	  Largeur du plateau
	/// \param height	  Hauteur du plateau
	/// \param cell_size  Taille des cases
	/// \game game		  Référence vers le jeu
	///
	Board (unsigned int x, unsigned int y, unsigned int width, unsigned int height,
		   unsigned int cell_size, Game& game);
	~Board ();

	///
	/// \brief Convertit une position (x, y) en indice
	/// \param pos Vecteur de position
	///
	unsigned posToInd (const sf::Vector2u pos) const;

	///
	/// \brief Convertit un couple de float (x, y) en indice
	/// \param x Position x
	/// \param y Position y
	///
	unsigned posToInd (const unsigned x, const unsigned y) const;

	///
	/// \brief Echange deux items du plateau
	/// \param src	Item A
	/// \param dest Item B
	///
	void swapItems (const unsigned int src, const unsigned int dest);

	///
	/// \brief Teste si deux items sont voisins
	/// \param src	Item A
	/// \param dest	Item B
	/// \return Oui/Non
	///
	bool areNext(unsigned int src, unsigned int dest) const;

	///
	/// \brief Supprime l'item à la position ind
	/// \param ind Indice
	///
	void removeItemAt (const unsigned int ind);

	///
	/// \brief Met à jour le plateau
	///
	void update ();

	///
	/// \brief Appelle updateLine pour chaque ligne et chaque colonne
	///
	void updateRowsAndCols ();

	///
	/// \brief Met à jour les positions pour chaque item
	///
	void updatePositions();

	///
	/// \brief Remet à zéro le dernier score obtenu
	///
	void resetLastScore();

	///
	/// \brief checkMovement
	/// \param ind_first_item
	/// \param ind_second_item
	/// \return
	///
	bool checkMovement (unsigned ind_first_item, unsigned ind_second_item) const;

	const std::vector<std::unique_ptr<Item>>& getItems () const;
	std::unique_ptr<Item>& getItemAt (const unsigned int ind);

	unsigned int getTotalSize () const;
	unsigned int getRowsCount () const;
	unsigned int getColsCount () const;
	unsigned int getCellSize () const;

	const sf::Rect<unsigned int>& getDimensions () const;
	const sf::Sprite& getBoardShape() const;

	bool areItemsMoving();
	bool isStable() const;

private:
	unsigned int cell_size;
	unsigned int total_size;
	unsigned int cols;
	unsigned int rows;

	sf::Rect<unsigned int> dimensions;

	std::vector<std::unique_ptr<Item>> items;

	std::unique_ptr<ItemGenerator> item_generator;

	sf::Sprite board_shape;
	sf::Texture board_shape_texture;

	unsigned int last_move_score;
	unsigned int combo;

	Game& game;

	///
	/// \brief Remplace l'item par un nouveau à la position (x, y)
	/// \param x Position x
	/// \param y Position y
	///
	void changeItem(unsigned int x, unsigned int y);

	///
	/// \brief Change tous les items détruits
	///
	void fillBlanks();

	///
	/// \brief Mets a jour une ligne, horizontale ou verticale.
	/// \param begin Indice du début de ligne.
	/// \param end Indice de la fin de la ligne.
	/// \param offset Différence entre deux items successifs
	///
	/// Offset vaut, a priori, soit 1 soit width.
	/// En effet, on cherchera soit a mettre a jour horizontalement, avec offset = 1,
	/// soit horizontalement, avec offset = width.
	///
	void updateLine (const unsigned int begin, const unsigned int end, const unsigned int offset);

	///
	/// \brief Détruit tous les items entre begin et end
	/// \param begin  Début
	/// \param end	  Fin
	/// \param offset Décalage (1 pour Horizontal et "largeur" pour Vertical)
	///
	void markForRemoval(unsigned int begin, unsigned int end, unsigned int offset);

	///
	/// \brief Fait remonter les items détruits dans la colonne col
	/// \param col Colonne concernée
	///
	void applyGravity(const unsigned int col);

	///
	/// \brief Remplit toute la grille avec les items aléatoires
	///
	void randomFill ();

	///
	/// \brief Vérifie si, après déplacement, le coup est valide
	/// \param source Item A
	/// \param dest	  Item B
	/// \return Oui/Non
	///
	bool validNeighbor (int source, int dest) const;
};

#endif /* INCLUDED_BOARD_HPP */
