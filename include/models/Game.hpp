#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <stack>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>

#include "conditions/Condition.hpp"
#include "Board.hpp"

///
/// \brief Modèle de jeu
///
class Game
{
public:
	///
	/// \brief Constructeur du jeu
	/// \param x		  Position x du plateau
	/// \param y		  Position y du plateau
	/// \param width	  Largeur du plateau
	/// \param height	  Hauteur du plateau
	/// \param cell_size  Taille des cases
	///
	Game(unsigned int x, unsigned int y, unsigned int width, unsigned int height,
			 unsigned int cell_size);
	virtual ~Game();

	///
	/// \brief Enregistre la position d'un clic
	/// \param x  Position x
	/// \param y  Position y
	///
	void setClickPosition(const float x, const float y);

	///
	/// \brief Enregistre la position d'un relâchement de clic
	/// \param x  Position x
	/// \param y  Position y
	///
	void setReleasePosition(const float x, const float y);

	///
	/// \brief Exécute un mouvement
	///
	/// Le mouvement est éxécuté seulement si le coup est valide
	///
	void executeMovement();

	///
	/// \brief Met à jour le jeu et le plateau
	///
	void updateGame();

	///
	/// \brief Ajoute des points au score
	/// \param value Valeur à ajouter
	///
	void addPoints(unsigned int value);

	///
	/// \brief Change le combo courant
	/// \param combo Valeur du combo
	///
	void setCombo(unsigned int combo);

	///
	/// \brief Définit si les évènements sont pris en compte ou non
	/// \param value Oui/Non
	///
	void setActive (bool value);

	Board& getBoard ();

	unsigned int getScore() const;
	unsigned int getCombo() const;
	unsigned int getGoalScore() const;
	unsigned int getLevel() const;

	Condition& getCondition ();
	const Condition& getCondition () const;
 
	bool isActive ();
	bool isGameOver();

private:
	Board board;

	sf::Vector2u first_item;
	sf::Vector2u second_item;

	bool first_selected;
	bool second_selected;

	bool active_input;

	unsigned int score;
	unsigned int combo;

	unsigned int level;
	unsigned int score_goal;

	float goal_coef;
	unsigned int tries_added;

	bool near_gameover;
	bool gameover;

	std::unique_ptr<Condition> condition;
	sf::Clock endClock;

	std::stack<sf::Vector2u> move_registered;

	void initializeGame();
	void registerMove(unsigned int source, unsigned int target);
};

#endif // GAME_HPP
