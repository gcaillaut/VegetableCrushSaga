#include "EndView.hpp"

#include <SFML/Window/Event.hpp>

#include "EndController.hpp"
#include "Globals.hpp"

#include "Game.hpp"

EndView::EndView(Controller *controller, sf::RenderWindow &window):
  View(controller),
  window(window)
{
  rectangle.setPosition(0, 0);
  rectangle.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
  rectangle.setFillColor(sf::Color(0, 0, 0, 0));

  auto font = globals.getFontManager().getRessource("wombo_font");

  gameover_text.setFont(*font);
  gameover_text.setColor(sf::Color(255, 0, 0, 64));
  gameover_text.setCharacterSize(300);
  gameover_text.setString("Game Over");
  gameover_text.setOrigin(gameover_text.getGlobalBounds().width / 2,
						  gameover_text.getGlobalBounds().height / 2);
  gameover_text.setPosition(window.getSize().x / 2, window.getSize().y / 5);

  buttons.push_back(sfg::Button::Create("Recommencer"));
  buttons.push_back(sfg::Button::Create("Quitter"));

  box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 25.f);
  for (sfg::Button::Ptr& button: buttons)
  {
	button->SetClass("button");
	box->Pack(button);
  }

  sfgWindow = sfg::Window::Create();
  sfgWindow->SetTitle("Menu");
  sfgWindow->SetPosition(sf::Vector2f(window.getSize().x / 4, window.getSize().y / 1.75));
  sfgWindow->SetStyle(sfg::Window::NO_STYLE);
  sfgWindow->SetRequisition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 3));

  sfgWindow->Add(box);
  sfgDesktop.Add(sfgWindow);

  sfgDesktop.GetEngine().SetProperty(".button", "BackgroundColor", sf::Color(0, 0, 0, 127));
  sfgDesktop.GetEngine().SetProperty(".button", "BorderWidth", 3.f);
  sfgDesktop.GetEngine().SetProperty(".button", "BorderColorShift", 0);
  sfgDesktop.GetEngine().SetProperty(".button", "FontSize", 18);

  buttons[0]->GetSignal(sfg::Button::OnLeftClick).Connect([this, &controller](){
	static_cast<EndController*>(controller)->onRecommencer();
	running = false;
  });

  buttons[1]->GetSignal(sfg::Button::OnLeftClick).Connect([this, &controller](){
	static_cast<EndController*>(controller)->onQuitter();
	running = false;
  });
}

EndView::~EndView()
{
}

void EndView::clear()
{
  window.clear(sf::Color::White);
}

void EndView::draw()
{
  window.draw(globals.getLastCapture());
  window.draw(rectangle);
  window.draw(gameover_text);

  if (gameover_clock.getElapsedTime().asSeconds() > 4)
	sfgui.Display(window);
}

void EndView::display()
{
  window.display();
}

void EndView::sendEvents()
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
		  globals.shutdown();
		  running = false;
		}
		break;

	  default:
		break;
	}
  }
}

void EndView::loop()
{
  gameover_clock.restart();

  while (running)
  {
	sendEvents();

	sfgDesktop.Update(1.f);
	updateText();

	clear();
	draw();
	display();
  }
}

void EndView::updateText()
{
  if (gameover_clock.getElapsedTime().asSeconds() < 4)
  {
	sf::Color rectangleColor = rectangle.getFillColor();
	sf::Color textColor = gameover_text.getColor();

	float delta = (float)(1.f/60.f * 60.f);
	rectangleColor.a += (rectangleColor.a + delta > 255 ? 0 : std::ceil(delta));
	textColor.a += (textColor.a + delta > 255 ? 0 : std::ceil(delta));

	rectangle.setFillColor(rectangleColor);
	gameover_text.setColor(textColor);
  }
}
