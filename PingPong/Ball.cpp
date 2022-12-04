#include "Ball.h"

Ball::Ball(shared_ptr<RenderWindow> const& windowPtr) : GraphicBase(windowPtr)
{
	std::cout << "Ball()\n";
}

Ball::~Ball()
{
	std::cout << "~Ball()\n";
}

void Ball::Setup(float radius, Vector2f const& startPos, Color const& clr, float thick, Color const& thicClr)
{
	circle_.setPointCount(500);
	circle_.setRadius(radius);
	circle_.setOrigin(radius, radius);
	circle_.setPosition(startPos);
	circle_.setFillColor(clr);
	circle_.setOutlineThickness(thick);
	circle_.setOutlineColor(thicClr);
}

void Ball::Update(float time)
{
	if (circle_.getPosition().y + circle_.getRadius() >= windowPtr_->getSize().y) {
		dirY = -1.0f;
	}
	else if (circle_.getPosition().y - circle_.getRadius() <= 0) {
		dirY = 1.0f;
	}
	else if (circle_.getPosition().x + circle_.getRadius() >= windowPtr_->getSize().x) {
		dirX = -1.0f;
	}
	else if (circle_.getPosition().x - circle_.getRadius() <= 0) {
		dirX = 1.0f;
	}

	dx = velocity * dirX * time;
	dy = velocity * dirY * time;

	circle_.move({ dx, dy });
}

void Ball::Draw()
{
	windowPtr_->draw(circle_);
}