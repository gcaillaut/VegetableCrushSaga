#include <SFML/Graphics/Texture.hpp>

#include "Globals.hpp"

#include "utils/Factory.hpp"

#include "models/items/BasicItem.hpp"
#include "models/items/SpecialItemBomb.hpp"
#include "models/items/SpecialItemVertical.hpp"
#include "models/items/SpecialItemHorizontal.hpp"

Globals globals;

Globals::Globals () :
  window(nullptr),
  current_view(nullptr),
  running(true),
  retry(true)
{
}

Globals::~Globals ()
{}

void Globals::init ()
{	
  try
  {
	YAML::Node config(YAML::LoadFile("assets/config.yml"));
	config = config["game"];

	sf::Vector2u window_size(config["graphic"]["window"]["size"][0].as<unsigned>(),
		config["graphic"]["window"]["size"][1].as<unsigned>());

	window.reset(new sf::RenderWindow(sf::VideoMode(window_size.x, window_size.y), "Vegetable Crush Saga", sf::Style::Default & ~sf::Style::Resize));
	window->setFramerateLimit(60);

	YAML::Node paths(config["system"]["paths"]);
	loadTextures(config["graphic"]["textures"], paths["texture_pack"].as<std::string>());
	loadFonts(config["graphic"]["fonts"], paths["font_pack"].as<std::string>());

	YAML::Node items(config["gameplay"]["items"]);
	loadItems(items);
  }
  catch (YAML::ParserException e)
  {
	std::cerr << "Le fichier de config n'est pas aux normes !" << std::endl;
	std::cerr << e.what() << std::endl;
	exit(EXIT_FAILURE);
  }
}

View* Globals::getCurrentView () const
{
  return current_view;
}

void Globals::setCurrentView (std::string name)
{
  current_view = this->getView(name);
  current_view->activate();
}

const Factory<Item>& Globals::getItemFactory () const
{
  return item_factory;
}

TextureManager& Globals::getTextureManager ()
{
  return texture_manager;
}

FontManager& Globals::getFontManager ()
{
  return font_manager;
}

sf::RenderWindow& Globals::getWindow ()
{
  return *window;
}

void Globals::gameLoop()
{
  while (running)
  {
	current_view->loop();
  }
}

void Globals::shutdown()
{
  current_view->deactivate();
  running = false;
}

void Globals::addView(std::string name, View *view)
{
  if (view_map.find(name) == view_map.end())
  {
	view_map[name] = view;
  }
}

View* Globals::getView(std::string name)
{
  if (view_map.find(name) != view_map.end())
  {
	return view_map[name];
  }
  else
  {
	return nullptr;
  }
}

void Globals::captureScreen()
{
  sf::Image image(window->capture());
  gameTexture.loadFromImage(image);
  gameSprite.setTexture(gameTexture);
}

const sf::Sprite &Globals::getLastCapture() const
{
  return gameSprite;
}

bool Globals::isRetrying()
{
  return retry;
}

void Globals::setRetry(bool value)
{
  retry = value;
}

void Globals::activate()
{
  running = true;
}

void Globals::clearViews()
{
  view_map.clear();
}

bool Globals::loadTextures(YAML::Node node, const std::string & path)
{
  if (!node)
	return false;

  for (auto n: node)
  {
	std::string name(n.first.as<std::string>());
	std::string filename(n.second.as<std::string>());

	texture_manager.createResource(name);
	texture_manager.getResource(name)->loadFromFile(path + "/" + filename);
  }

  return true;
}

bool Globals::loadFonts(YAML::Node node, const std::string & path)
{
  if (!node)
	return false;

  for (auto n: node)
  {
	std::string name(n.first.as<std::string>());
	std::string filename(n.second.as<std::string>());

	font_manager.createResource(name);
	font_manager.getResource(name)->loadFromFile(path + "/" + filename);
  }

  return true;

}

bool Globals::loadItems (YAML::Node node)
{
  unsigned score_basic(node["values"]["basic"].as<unsigned>());
  unsigned score_special(node["values"]["special"].as<unsigned>());

  for (size_t i(0) ; i < node["names"]["basic"].size() ; ++i)
  {
	std::string name(node["names"]["basic"][i].as<std::string>());
	if (!texture_manager.getResource(name))
	{
	  std::cout << "Attention, la texture de \"" << name << "\" n'existe pas !" << std::endl;
	}
	else
	{
	  item_factory.registerObject(name, [name,score_basic]() {
		return createBasicItem(name, score_basic);
	  });
	}
  }

  for (size_t i(0) ; i < node["names"]["special"].size() ; ++i)
  {
	std::string name(node["names"]["special"][i].as<std::string>());
	if (!texture_manager.getResource(name))
	{
	  std::cout << "Attention, la texture de \"" << name << "\" n'existe pas !" << std::endl;
	}
	else
	{
	  if (name.find("Special") != std::string::npos)
	  {
		item_factory.registerObject(name, [name,score_special]() {
		  return createSpecialItemBomb(name, score_special);
		});
	  }

	  else if (name.find("Horizontal") != std::string::npos)
	  {
		item_factory.registerObject(name, [name,score_special]() {
		  return createSpecialItemHorizontal(name, score_special);
		});
	  }

	  if (name.find("Vertical") != std::string::npos)
	  {
		item_factory.registerObject(name, [name,score_special]() {
		  return createSpecialItemVertical(name, score_special);
		});
	  }
	}
  }

  return true;
}

Item* Globals::createBasicItem(std::string name, unsigned int value)
{
  Item* item(new BasicItem(name, value));
  item->setTexture(*globals.getTextureManager().getResource(name));
  return item;
}

Item* Globals::createSpecialItemBomb(std::string name, unsigned int value)
{
  // 7 est la taille de "Special"
  std::string basic_name(name.substr(0, name.size() - 7));
  Item* item(new SpecialItemBomb(basic_name, value));
  item->setTexture(*globals.getTextureManager().getResource(name));
  return item;
}

Item* Globals::createSpecialItemHorizontal(std::string name, unsigned int value)
{
  // 10 est la taille de "Horizontal"
  std::string basic_name(name.substr(0, name.size() - 10));
  Item* item(new SpecialItemHorizontal(basic_name, value));
  item->setTexture(*globals.getTextureManager().getResource(name));
  return item;
}

Item* Globals::createSpecialItemVertical(std::string name, unsigned int value)
{
  // 8 est la taille de "Vertical"
  std::string basic_name(name.substr(0, name.size() - 8));
  Item* item(new SpecialItemVertical(basic_name, value));
  item->setTexture(*globals.getTextureManager().getResource(name));
  return item;
}
