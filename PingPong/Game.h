#pragma once

#include "GraphicBase.h"
#include "Ball.h"
#include "Panel.h"

#include <list>

using std::list;
using std::string;

class Game final : public GraphicBase
{
private:
	RectangleShape backGround_;
	shared_ptr<Ball> ball_;
	shared_ptr<Panel> player_;

public:
	Game();
	~Game();
	Game(Game const&) = delete;
	Game(Game&&) = delete;
	Game& operator= (Game const&) = delete;
	Game& operator= (Game&&) = delete;

	int Run();
	bool Init(string const& cfgFileName);

private:
	void Update(float time) override;
	void Draw() override;
};

