#include <SFML/Window/Event.hpp>

#include "views/MenuView.hpp"
#include "controllers/MenuController.hpp"

#include "Globals.hpp"

MenuView::MenuView(Controller *controller, sf::RenderWindow &window):
  View(controller),
  window(window)
{
  rectangle.setPosition(0, 0);
  rectangle.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
  rectangle.setFillColor(sf::Color(0, 0, 0, 127));

  buttons.push_back(sfg::Button::Create("Retour"));
  buttons.push_back(sfg::Button::Create("Quitter"));

  box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 50.f);
  for (sfg::Button::Ptr& button: buttons)
  {
	button->SetClass("button");
	box->Pack(button);
  }

  sfgWindow = sfg::Window::Create();
  sfgWindow->SetTitle("Menu");
  sfgWindow->SetPosition(sf::Vector2f(window.getSize().x / 4, window.getSize().y / 4));
  sfgWindow->SetStyle(sfg::Window::NO_STYLE);
  sfgWindow->SetRequisition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

  sfgWindow->Add(box);
  sfgDesktop.Add(sfgWindow);

  sfgDesktop.GetEngine().SetProperty(".button", "BackgroundColor", sf::Color(0, 0, 0, 127));
  sfgDesktop.GetEngine().SetProperty(".button", "BorderWidth", 3.f);
  sfgDesktop.GetEngine().SetProperty(".button", "BorderColorShift", 0);
  sfgDesktop.GetEngine().SetProperty(".button", "FontSize", 18);

  buttons[0]->GetSignal(sfg::Button::OnLeftClick).Connect([this, &controller](){
	static_cast<MenuController*>(controller)->onRetour();
	running = false;
  });

  buttons[1]->GetSignal(sfg::Button::OnLeftClick).Connect([this, &controller](){
	static_cast<MenuController*>(controller)->onQuitter();
	running = false;
  });
}

MenuView::~MenuView()
{
}

void MenuView::clear()
{
  window.clear(sf::Color::White);
}

void MenuView::draw()
{
  window.draw(globals.getLastCapture());
  window.draw(rectangle);

  sfgui.Display(window);
}

void MenuView::display()
{
  window.display();
}

void MenuView::sendEvents()
{
  sf::Event event;
  while (window.pollEvent(event))
  {
	sfgDesktop.HandleEvent(event);

	switch (event.type)
	{
	  case sf::Event::Closed:
		globals.shutdown();
		running = false;
		break;

	  case sf::Event::KeyPressed:
		if (event.key.code == sf::Keyboard::Escape)
		{
		  globals.setCurrentView("Game");
		  running = false;
		}
		break;

	  case sf::Event::LostFocus:
		controller->onLostFocus();
		break;

	  case sf::Event::GainedFocus:
		controller->onGainedFocus();
		break;

	  default:
		break;
	}
  }
}

void MenuView::loop()
{
  while (running)
  {
	sendEvents();

	sfgDesktop.Update(1.f);

	clear();
	draw();
	display();
  }
}
