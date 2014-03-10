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

class Board
{
  public:
	Board (unsigned int x, unsigned int y, unsigned int width, unsigned int height,
		   unsigned int cell_size, Game& game);
	~Board ();

	const std::vector<std::unique_ptr<Item>>& getItems () const;
	std::unique_ptr<Item>& getItemAt (const unsigned int ind);

	unsigned int getTotalSize () const;
	unsigned int getRowsCount () const;
	unsigned int getColsCount () const;
	unsigned int getCellSize () const;

	const sf::Rect<unsigned int>& getDimensions () const;
	const sf::Sprite& getBoardShape() const;

	unsigned posToInd (const sf::Vector2u pos) const;
	unsigned posToInd (const unsigned x, const unsigned y) const;

	void swapItems (const unsigned int src, const unsigned int dest);
	bool areNext(unsigned int src, unsigned int dest) const;

	bool isStable() const;

	void updateRowsAndCols ();

	void update ();

	void updatePositions();
	bool areItemsMoving();

	void resetLastScore();

	bool checkMovement (unsigned ind_first_item, unsigned ind_second_item) const;

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

	void changeItem(unsigned int x, unsigned int y);

	void fillBlanks();

	/**
   * \brief Mets a jour une ligne, horizontale ou verticale.
   * \param begin Indice du début de ligne.
   * \param end Indice de la fin de la ligne.
   * \param offset Différence entre deux items successifs
   *
   * Offset vaut, a priori, soit 1 soit width.
   * En effet, on cherchera soit a mettre a jour horizontalement, avec offset = 1,
   * soit horizontalement, avec offset = width.
   */
	void updateLine (const unsigned int begin, const unsigned int end, const unsigned int offset);

	void markForRemoval(unsigned int begin, unsigned int end, unsigned int offset);

	void applyGravity(const unsigned int col);

	void randomFill ();

	bool validNeighbor (int source, int dest) const;
};

#endif /* INCLUDED_BOARD_HPP */
