#pragma once

#include "GraphicBase.h"
#include "GameObjectBase.h"

#include <iostream>

class Ball final : public GraphicBase, public GameObjectBase
{
private:
	// graphic object
	CircleShape circle;
	
public:
	Ball(shared_ptr<RenderWindow> const& windowPtr, unsigned id);

	Ball(Ball const&) = delete;
	Ball(Ball&&)      = delete;
	Ball& operator= (Ball const&) = delete;
	Ball& operator= (Ball&&)      = delete;

	~Ball();

	void Init(ifstream& cfgFile) override;
	void Control(Event const& event) override;
	void Update(float time)          override;
	void Draw()			             override;

	bool Contain(Vector2f const& pos) const noexcept override;
	Vector2f GetPos()			      const noexcept override;

	void SetPos(Vector2f const& pos);

	void SetDirs(float dirX, float dirY = 0.0f);
};
