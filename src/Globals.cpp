#include <SFML/Graphics/Texture.hpp>

#include "Globals.hpp"

#include "Item.hpp"
#include "Factory.hpp"
#include "BasicItem.hpp"

Globals globals;


Globals::Globals () :
  window(nullptr),
  current_view(nullptr),
  running(true)
{
}

Globals::~Globals ()
{}

void Globals::init ()
{	
	YAML::Node config(YAML::LoadFile("assets/config.yml"));
	
	if (!config["graphic"]["window"]["size"])
		exit(EXIT_FAILURE);

	if (!config["graphic"]["textures"])
		exit(EXIT_FAILURE);
	
	sf::Vector2u window_size(config["graphic"]["window"]["size"][0].as<unsigned>(),
													 config["graphic"]["window"]["size"][1].as<unsigned>());

  window.reset(new sf::RenderWindow(sf::VideoMode(window_size.x, window_size.y), "Test", sf::Style::Default & ~sf::Style::Resize));
  window->setFramerateLimit(60);

	loadTextures(config["graphic"]["textures"]);


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

TexturesManager& Globals::getTexturesManager ()
{
  return textures_manager;
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

bool Globals::loadTextures(YAML::Node node)
{
	if (!node["texture_pack"])
		return false;

	std::string texture_pack = node["texture_pack"].as<std::string>();

	if (!node["items"])
		return false;

	for (auto n: node["items"])
		{
			std::string name(n.first.as<std::string>());
			std::string filename(n.second.as<std::string>());
 
			textures_manager.createRessource(name);
			textures_manager.getRessource(name)->loadFromFile(texture_pack + "/" + filename);

			item_factory.registerObject(name, [name]() {
					return createItem(name, 5);
				});
		}

  return true;
}

Item* Globals::createItem(std::string name, unsigned int value)
{
	Item* item(new BasicItem(name, value));
	item->setTexture(*globals.getTexturesManager().getRessource(name));
	return item;
}
