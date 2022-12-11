#pragma once

#include "PlayerPanel.h"

class BotPanel final : public PlayerPanel
{
public:
	BotPanel(shared_ptr<RenderWindow> const& windowPtr, unsigned id);

	BotPanel(BotPanel const&) = delete;
	BotPanel(BotPanel&&)      = delete;
	BotPanel& operator= (BotPanel const&) = delete;
	BotPanel& operator= (BotPanel&&)      = delete;

	~BotPanel();

	void Init(ifstream& cfgFile)     override;
	void Control(Event const& event/* = Event()*/) override;
	void Update(float time)          override;
	void Draw()				         override;

	//bool Contain(Vector2f const& pos) const noexcept override;
	//Vector2f GetPos()				  const noexcept override;
};
