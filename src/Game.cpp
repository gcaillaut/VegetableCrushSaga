#include "Game.hpp"

Game game;

Game::Game () :
  window(nullptr),
  current_view(nullptr)
{}

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

sf::RenderWindow& Game::getWindow ()
{
  return *window;
}
