#pragma once

#include "GraphicBase.h"
#include <sstream>

class Info final : public GraphicBase
{
private:
	// params
	string name;
	unsigned playerPoints = 0, botPoints = 0, countOfBallReflections = 0;

	// graphic objects
	RectangleShape block;
	Font outTextFontGameInfo;
	Text outTextGameInfo;
	std::ostringstream textStream;

	String outInfoString;

public:
	Info(shared_ptr<RenderWindow> const& windowPtr, unsigned id);

	Info(Info const&) = delete;
	Info(Info&&)      = delete;
	Info& operator= (Info const&) = delete;
	Info& operator= (Info&&)      = delete;

	~Info();

	void Init(ifstream& cfgFile)	 override;
	void Control(Event const& event) override;
	void Update(float time = 0.0f)   override;
	void Draw()			             override;

	void SetPlayerBotBallPoints(unsigned playerPoints, unsigned botPoints, unsigned countOfBallReflections);
};
