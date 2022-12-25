#pragma once

#include "GraphicBase.h"
#include "GameObjectBase.h"

class PlayerPanel : public GraphicBase, public GameObjectBase
{
protected:
	// graphic object
	RectangleShape line;
	// 
	float halfWeight = 0.0f, halfHeight = 0.0f;
	Keyboard::Key lastKey = Keyboard::O;

public:
	PlayerPanel(shared_ptr<RenderWindow> const& windowPtr, unsigned id);

	PlayerPanel(PlayerPanel const&) = delete;
	PlayerPanel(PlayerPanel&&)      = delete;
	PlayerPanel& operator= (PlayerPanel const&) = delete;
	PlayerPanel& operator= (PlayerPanel&&)      = delete;

	~PlayerPanel();

	void Init(ifstream& cfgFile)     override;
	void Control(Event const& event) override;
	void Update(float time)          override;
	void Draw()				         override;

	bool Contain(Vector2f const& pos) const noexcept override;
	Vector2f GetPos()				  const noexcept override;

	unsigned GetPoints()      const noexcept override;
	void IncPoints(unsigned points) noexcept override;
	void ResetPoints()			    noexcept override;
};
