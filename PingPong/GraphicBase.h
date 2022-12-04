#pragma once

#include <SFML/Graphics.hpp>

using std::shared_ptr;
using sf::Vector2f;
using sf::CircleShape;
using sf::RenderWindow;
using sf::RectangleShape;
using sf::VideoMode;
using sf::Event;
using sf::Color;
using sf::Clock;

class GraphicBase
{
protected:
	shared_ptr<RenderWindow> windowPtr_ = nullptr;

	GraphicBase(shared_ptr<RenderWindow> const& windowPtr);
	~GraphicBase();

public:
	virtual void Update(float time) = 0;
	virtual void Draw()	  = 0;
};