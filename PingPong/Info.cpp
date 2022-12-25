#include "Info.h"

Info::Info(shared_ptr<RenderWindow> const& windowPtr, unsigned id) : GraphicBase(windowPtr, id)
{
	//std::cout << "Info()\n";
}

Info::~Info()
{
	//std::cout << "Info()\n";
}

void Info::Init(ifstream& cfgFile)
{
	string fontName;
	unsigned fontSize;
	unsigned tR, tG, tB;
	float width, height, blockPosX, blockPosY;
	float thicknes;
	unsigned bR, bG, bB, bOR, bOG, bOB;

	if (!(cfgFile >> name >> fontName >> fontSize >> tR >> tG >> tB >> width >> height >> blockPosX >> blockPosY
		>> bR >> bG >> bB >> thicknes >> bOR >> bOG >> bOB)) {
			throw invalid_argument("Error of init InfoPanel class");
	}

	if (!outTextFontGameInfo.loadFromFile(fontName)) {
		throw invalid_argument("Font: " + fontName + " not found");
	}

	block.setSize({ width, height });
	block.setOrigin(width / 2.0f, height / 2.0f);
	block.setPosition(blockPosX, blockPosY);
	block.setFillColor(Color(bR, bG, bB));
	block.setOutlineThickness(thicknes);
	block.setOutlineColor(Color(bOR, bOG, bOB));

	outTextGameInfo.setFont(outTextFontGameInfo);
	outTextGameInfo.setCharacterSize(fontSize);
	outTextGameInfo.setFillColor(Color(tR, tG, tB));
	outTextGameInfo.setOutlineColor(Color::Black);
	outTextGameInfo.setOutlineThickness(1.0f);
	outTextGameInfo.setOrigin(outTextGameInfo.getLocalBounds().width / 2.0f, outTextGameInfo.getLocalBounds().height / 2.0f);
	outTextGameInfo.setPosition(block.getPosition());

	SetPlayerBotBallPoints(0, 0, 0);
	Update();
}

void Info::Control(Event const& event)
{

}

void Info::Update(float time)
{
	outTextGameInfo.setString(outInfoString);
	outTextGameInfo.setOrigin(outTextGameInfo.getLocalBounds().width / 2.0f, outTextGameInfo.getLocalBounds().height / 2.0f);
}

void Info::Draw()
{
	windowPtr->draw(block);
	windowPtr->draw(outTextGameInfo);
}

void Info::SetPlayerBotBallPoints(unsigned playerPoints, unsigned botPoints, unsigned countOfBallReflections)
{
	this->playerPoints           = playerPoints;
	this->botPoints              = botPoints;
	this->countOfBallReflections = countOfBallReflections;

	outInfoString = "Player: " + std::to_string(playerPoints) + " | Bot: " + std::to_string(botPoints) + " | Reflections: " + std::to_string(countOfBallReflections);
}
