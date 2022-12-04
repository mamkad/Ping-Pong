#pragma once

#include "GraphicBase.h"
#include <iostream>

class Panel final : public GraphicBase
{
private:
	RectangleShape line_;
	float dy = 0.0f, velocity = 200.0f, dirY = 0.0f;

public:
	Panel(shared_ptr<RenderWindow> const& windowPtr);
	~Panel();

	void Setup(Vector2f const& size, Vector2f const& pos, Color const clr, float thick, Color const& thicClr);

	void Update(float time) override;
	void Draw() override;

	void OnControl(Event const& event);
};
