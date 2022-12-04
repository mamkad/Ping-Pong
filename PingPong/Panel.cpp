#include "Panel.h"

Panel::Panel(shared_ptr<RenderWindow> const& windowPtr) : GraphicBase(windowPtr)
{
	std::cout << "Panel()\n";
}

Panel::~Panel()
{
	std::cout << "~Panel()\n";
}

void Panel::Setup(Vector2f const& size, Vector2f const& pos, Color const clr, float thick, Color const& thicClr)
{
	line_.setSize(size);
	line_.setOrigin(size.x / 2, size.y / 2);
	line_.setPosition(pos);
	line_.setFillColor(clr);
	line_.setOutlineThickness(thick);
	line_.setOutlineColor(thicClr);
}

void Panel::Update(float time)
{
	dy = velocity * dirY * time;
	line_.move({ 0, dy });
}

void Panel::Draw()
{
	windowPtr_->draw(line_);
}

void Panel::OnControl(Event const& event)
{
	switch (event.key.code) {
		case sf::Keyboard::W: {
			dirY = -1.0f;
			break;
		}
		case sf::Keyboard::S: {
			dirY = 1.0f;
			break;
		}
	}
}