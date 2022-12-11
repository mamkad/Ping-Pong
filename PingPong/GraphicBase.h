#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>

using std::shared_ptr;
using sf::CircleShape;
using sf::RenderWindow;
using sf::RectangleShape;
using sf::VideoMode;
using sf::Event;
using sf::Vector2f;
using sf::Color;
using sf::Clock;
using sf::Keyboard;
using sf::Mouse;

using std::ifstream;
using std::string;
using std::invalid_argument;

class GraphicBase
{
protected:
	shared_ptr<RenderWindow> windowPtr = nullptr;
	unsigned id = 0;

	GraphicBase(shared_ptr<RenderWindow> const& windowPtr, unsigned id);
	virtual ~GraphicBase();

	unsigned GetId() const noexcept;
	Vector2f const& MousePos() const noexcept;

public:
	virtual void Init(ifstream& cfgFile)     = 0;
	virtual void Control(Event const& event) = 0;
	virtual void Update(float time) = 0;
	virtual void Draw()	            = 0;
};