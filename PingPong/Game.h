#pragma once

#include "GraphicBase.h"
#include "Ball.h"
#include "PlayerPanel.h"
#include "BotPanel.h"

class GameLogicParams final
{
private:
	bool isActive_ = false;
	unsigned addedPoints = 25, maxPoints = 200;
	unsigned player1Points = 0, botPoints = 0;

public:
	void SetActive(bool mode) noexcept;
	bool IsActive()     const noexcept;

	void AddPointsToPlayer()         noexcept;
	unsigned GetPlayerPoints() const noexcept;

	void AddPointsToBot()         noexcept;
	unsigned GetBotPoints() const noexcept;

	bool IsOver() const noexcept;

	void Save();
	void Read();
};

class Game final : public GraphicBase
{
private:
	// 
	RectangleShape			backGround;
	// game objects
	shared_ptr<Ball>		ball   = nullptr;
	shared_ptr<PlayerPanel> player = nullptr;
	shared_ptr<BotPanel>    bot    = nullptr;
	// game params
	Vector2f centralPos;
	bool isActive = false;

public:
	Game(string const& cfgFileName);

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

