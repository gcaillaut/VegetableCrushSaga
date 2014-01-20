#include "Game.hpp"
#include "Item.hpp"
#include "Factory.hpp"

#include "BasicItem.hpp"
#include "createFunc.hpp"

Game game;


Game::Game () :
  window(nullptr),
  current_view(nullptr)
{
  item_factory.registerObject("Salad", &createSalad);
  item_factory.registerObject("Carrot", &createCarrot);
}

Game::~Game ()
{}

void Game::init ()
{
  window.reset(new sf::RenderWindow(sf::VideoMode(640, 480), "Vegetable Crush Saga Bitch !"));
}

View* Game::getCurrentView () const
{
  return current_view;
}

void Game::setCurrentView (View *view)
{
  current_view = view;
}

const Factory<Item>& Game::getItemFactory () const 
{
  return item_factory;
}

TexturesManager& Game::getTexturesManager ()
{
  return textures_manager;
}

sf::RenderWindow& Game::getWindow ()
{
  return *window;
}
