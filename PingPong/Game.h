#pragma once

#include "GraphicBase.h"
#include "Ball.h"
#include "PlayerPanel.h"
#include "BotPanel.h"
#include "Info.h"

class Game final : public GraphicBase
{
private:
	// 
	RectangleShape			backGround;

	// game objects
	shared_ptr<Ball>		ball      = nullptr;
	shared_ptr<PlayerPanel> player    = nullptr;
	shared_ptr<BotPanel>    bot       = nullptr;
	shared_ptr<Info>		infoPanel = nullptr;

	// game params
	Vector2f centralPos;

	unsigned dPoints = 0, maxPoints = 0;

	bool isActive = false;

public:
	Game(string const& cfgFileName, string const& logFileName);

	Game(Game const&) = delete;
	Game(Game&&)      = delete;
	Game& operator= (Game const&) = delete;
	Game& operator= (Game&&)      = delete;

	~Game();

	int Run();

private:
	void Init(ifstream& cfgFile)     override;
	void Control(Event const& event) override;
	void Update(float time)	override;
	void Draw()			    override;
};

