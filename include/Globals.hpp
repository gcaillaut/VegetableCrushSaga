#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>

#include <yaml-cpp/yaml.h>

#include "views/View.hpp"
#include "utils/Factory.hpp"
#include "utils/ResourceManager.hpp"


class Item;

typedef ResourceManager<sf::Texture, std::string> TextureManager;
typedef ResourceManager<sf::Font, std::string> FontManager;

///
/// \brief Fonctions et objets globaux
///
class Globals
{
public:
	Globals ();
	~Globals ();

	///
	/// \brief Initialise le jeu à l'aide du fichier de configuration
	///
	void init ();

	///
	/// \brief Boucle de jeu principale
	///
	void gameLoop();

	///
	/// \brief Arrête la boucle de jeu
	///
	void shutdown();

	///
	/// \brief Ajoute la vue dans la map
	/// \param name	Nom de la vue
	/// \param view	Vue
	///
	void addView(std::string name, View* view);

	///
	/// \brief Définit la vue actuelle
	/// \param name	Nom de la vue
	///
	void setCurrentView (std::string name);

	///
	/// \brief Supprime toutes les vues
	///
	void clearViews();

	///
	/// \brief Enregistre une capture d'écran
	///
	void captureScreen();

	///
	/// \brief Définit si le jeu recommencera une fois terminé
	/// \param value Oui/Non
	///
	void setRetry(bool value);

	///
	/// \brief Réactive la boucle de jeu
	///
	void activate();

	TextureManager& getTextureManager ();
	FontManager& getFontManager ();
	sf::RenderWindow& getWindow ();

	View* getView(std::string name);
	View* getCurrentView () const;

	const Factory<Item>& getItemFactory () const;
	const sf::Sprite& getLastCapture() const;

	bool isRetrying();

private:
	///
	/// \brief Charge les textures du jeu
	/// \param node	Node YAML
	/// \param path	Chemin du pack de textures
	/// \return	Oui si tout s'est bien passé. Non sinon.
	///
	bool loadTextures(YAML::Node node, const std::string & path);

	///
	/// \brief Charge les items
	/// \param node Node YAML
	/// \return Oui si tout s'est bien passé. Non sinon.
	///
	bool loadItems (YAML::Node node);

	///
	/// \brief Charge les polices de caractères
	/// \param node Node YAML
	/// \param path Chemin du pack de polices
	/// \return Oui si tout s'est bien passé. Non sinon.
	///
	bool loadFonts(YAML::Node node, const std::string & path);

	static Item* createBasicItem(std::string name, unsigned int value);
	static Item* createSpecialItemBomb(std::string name, unsigned int value);
	static Item* createSpecialItemHorizontal(std::string name, unsigned int value);
	static Item* createSpecialItemVertical(std::string name, unsigned int value);
   
	std::unique_ptr<sf::RenderWindow> window;
	View *current_view;

	Factory<Item> item_factory;
	TextureManager texture_manager;
	FontManager font_manager;

	std::map<std::string, View*> view_map;

	bool running;
	bool retry;

	sf::Texture gameTexture;
	sf::Sprite gameSprite;
};

extern Globals globals;

#endif /* GLOBALS_HPP */
