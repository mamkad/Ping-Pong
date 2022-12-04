#pragma once

#include "GraphicBase.h"
#include <iostream>

class Ball final : public GraphicBase
{
private:
	CircleShape circle_;
	float dx = 0.0f, dy = 0.0f, velocity = 200.0f;
	float dirX = 1.0f, dirY = 1.0f;

public:
	Ball(shared_ptr<RenderWindow> const& windowPtr);
	~Ball();

	void Setup(float radius, Vector2f const& startPos, Color const& clr, float thick, Color const& thicClr);

	void Update(float time) override;
	void Draw() override;
};
