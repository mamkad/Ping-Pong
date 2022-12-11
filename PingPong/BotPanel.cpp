#include "BotPanel.h"

BotPanel::BotPanel(shared_ptr<RenderWindow> const& windowPtr, unsigned id) : PlayerPanel(windowPtr, id)
{
	std::cout << "BotPanel()\n";
}

BotPanel::~BotPanel()
{
	std::cout << "~BotPanel()\n";
}

void BotPanel::Init(ifstream& cfgFile)
{
	float width, height, botPanelX, botPanelY;
	float thicknes;
	unsigned bR, bG, bB, bOR, bOG, bOB;

	if (!(cfgFile >> name >> width >> height >> botPanelX >> botPanelY
		>> bR >> bG >> bB >> thicknes >> bOR >> bOG >> bOB
		>> velocity)) {
		throw invalid_argument("Error of init BotPanel class");
	}

	halfWeight = width / 2.0f;
	halfHeight = height / 2.0f;

	line.setSize({ width, height });
	line.setOrigin(halfWeight, halfHeight);
	line.setPosition(botPanelX, botPanelY);
	line.setFillColor(Color(bR, bG, bB));
	line.setOutlineThickness(thicknes);
	line.setOutlineColor(Color(bOR, bOG, bOB));
}

void BotPanel::Control(Event const& event) // хватать события игрока
{

}

void BotPanel::Update(float time)
{
	float dy = velocity * dirY * time;

	line.move({ 0.0f, dy });
}

void BotPanel::Draw()
{
	windowPtr->draw(line);
}
/*
bool BotPanel::Contain(Vector2f const& pos) const noexcept
{
	return ((line.getPosition().x - halfWeight) < pos.x && pos.x < (line.getPosition().x + halfWeight))
		&& ((line.getPosition().y - halfHeight) < pos.y && pos.y < (line.getPosition().y + halfHeight));
}

Vector2f BotPanel::GetPos() const noexcept
{
	return line.getPosition();
}*/