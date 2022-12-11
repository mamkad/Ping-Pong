#pragma once

#include "GraphicBase.h"

class Menu final : GraphicBase
{
public:

	Menu(shared_ptr<RenderWindow> const& windowPtr, unsigned id);

	Menu(Menu const&) = delete;
	Menu(Menu&&)	  = delete;
	Menu& operator= (Menu const&) = delete;
	Menu& operator= (Menu&&)      = delete;

	~Menu();

	void Init(ifstream& cfgFile)	 override;
	void Control(Event const& event) override;
	void Update(float time)          override;
	void Draw()			             override;
};
