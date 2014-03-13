#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>

#include <yaml-cpp/yaml.h>

#include "View.hpp"
#include "Factory.hpp"
#include "RessourceManager.hpp"


class Item;

typedef RessourcesManager<sf::Texture, std::string> TexturesManager;
typedef RessourcesManager<sf::Font, std::string> FontManager;

class Globals
{
public:
	Globals ();
	~Globals ();

	void init ();
	void gameLoop();
	void shutdown();

	View* getCurrentView () const;
	void setCurrentView (std::string name);

	const Factory<Item>& getItemFactory () const;
	TexturesManager& getTexturesManager ();
	FontManager& getFontManager ();
	sf::RenderWindow& getWindow ();

	void addView(std::string name, View* view);
	View* getView(std::string name);

	void captureScreen();
	const sf::Sprite& getLastCapture() const;

private:
	bool loadTextures(YAML::Node node, const std::string & path);
	bool loadItems (YAML::Node node);
	bool loadFonts(YAML::Node node, const std::string & path);

	static Item* createBasicItem(std::string name, unsigned int value);
	static Item* createSpecialItemBomb(std::string name, unsigned int value);
 
	std::unique_ptr<sf::RenderWindow> window;
	View *current_view;

	Factory<Item> item_factory;
	TexturesManager textures_manager;
	FontManager font_manager;

	std::map<std::string, View*> view_map;

	bool running;

	sf::Texture gameTexture;
	sf::Sprite gameSprite;
};

extern Globals globals;

#endif /* GLOBALS_HPP */
