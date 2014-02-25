#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "View.hpp"
#include "Factory.hpp"
#include "RessourceManager.hpp"

class Item;

typedef RessourcesManager<sf::Texture, std::string> TexturesManager;

class Globals
{
  public:
	Globals ();
	~Globals ();

	void init ();

	View* getCurrentView () const;
	void setCurrentView (View *view);

	const Factory<Item>& getItemFactory () const;
	TexturesManager& getTexturesManager ();
	sf::RenderWindow& getWindow ();

  private:
	std::unique_ptr<sf::RenderWindow> window;
	View *current_view;

	Factory<Item> item_factory;
	TexturesManager textures_manager;

	void addTexture(std::string name);
};

extern Globals globals;

#endif /* GLOBALS_HPP */