#include "BotPanel.h"

BotPanel::BotPanel(shared_ptr<RenderWindow> const& windowPtr, unsigned id) : PlayerPanel(windowPtr, id)
{
	//std::cout << "BotPanel()\n";
}

BotPanel::~BotPanel()
{
	//std::cout << "~BotPanel()\n";
}

void BotPanel::Init(ifstream& cfgFile)
{
	float width, height, botPanelX, botPanelY;
	float thicknes;
	unsigned bR, bG, bB, bOR, bOG, bOB;

	if (!(cfgFile >> name >> width >> height >> botPanelX >> botPanelY
		>> bR >> bG >> bB >> thicknes >> bOR >> bOG >> bOB
		>> velocity >> aimDistance >> fluctuationsDistance)) {
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
	float w = 30.0f, h = 10.0f;

	if (currentBallPos.x > float(windowPtr->getSize().x) - aimDistance) {
		if (GetPos().y < currentBallPos.y) {
			dirY = 1.0f;
		}
		else if (GetPos().y > currentBallPos.y) {
			dirY = -1.0f;
		}
	}
	else if (currentBallPos.x > float(windowPtr->getSize().x) - fluctuationsDistance) {
		dirY = cosf(w * time + h);
	}

	float y = GetPos().y;

	if ((y - halfHeight) < 0.0f) {
		dirY = 1.0f;
	}
	else if ((y + halfHeight) > float(windowPtr->getSize().y)) {
		dirY = -1.0f;
	}

	float dy = velocity * dirY * time;

	line.move({ 0.0f, dy });
}

void BotPanel::Draw()
{
	windowPtr->draw(line);
}

unsigned BotPanel::GetPoints() const noexcept
{
	return points;
}

void BotPanel::IncPoints(unsigned points) noexcept
{
	this->points += points;
}

void BotPanel::ResetPoints() noexcept
{
	points = 0;
}


bool BotPanel::Contain(Vector2f const& pos) const noexcept
{
	return ((line.getPosition().x - halfWeight) < pos.x && pos.x < (line.getPosition().x + halfWeight))
		&& ((line.getPosition().y - halfHeight) < pos.y && pos.y < (line.getPosition().y + halfHeight));
}

Vector2f BotPanel::GetPos() const noexcept
{
	return line.getPosition();
}

void BotPanel::SetBallPos(Vector2f const& ballPos) noexcept
{
	currentBallPos = ballPos;
}