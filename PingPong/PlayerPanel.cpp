#include "PlayerPanel.h"

PlayerPanel::PlayerPanel(shared_ptr<RenderWindow> const& windowPtr, unsigned id) : GraphicBase(windowPtr, id)
{
	//std::cout << "PlayerPanel()\n";
}

PlayerPanel::~PlayerPanel()
{
	//std::cout << "~PlayerPanel()\n";
}

void PlayerPanel::Init(ifstream& cfgFile)
{
	float width, height, playerPanelX, playerPanelY;
	float thicknes;
	unsigned bR, bG, bB, bOR, bOG, bOB;
	
	if (!(cfgFile >> name >> width >> height >> playerPanelX >> playerPanelY 
			>> bR >> bG >> bB >> thicknes >> bOR >> bOG >> bOB
				>> velocity)) {
		throw invalid_argument("Error of init PlayerPanel class");
	}

	halfWeight = width / 2.0f;
	halfHeight = height / 2.0f;

	line.setSize({ width, height });
	line.setOrigin(halfWeight, halfHeight);
	line.setPosition(playerPanelX, playerPanelY);
	line.setFillColor(Color(bR, bG, bB));
	line.setOutlineThickness(thicknes);
	line.setOutlineColor(Color(bOR, bOG, bOB));
}

void PlayerPanel::Control(Event const& event)
{
	Keyboard::Key key = event.key.code;

	switch (event.type) {
		case Event::KeyPressed: {
			if (key == Keyboard::W) {
				dirY = -1.0f;
			}
			else if (key == Keyboard::S) {
				dirY = 1.0f;
			}
			lastKey = key;
			break;
		}
		case Event::KeyReleased: {
			if (key == Keyboard::W || key == Keyboard::S) {
				dirY = 0.0f;
			}
			break;
		}
		default:
			break;
	}
}

void PlayerPanel::Update(float time)
{
	float y = line.getPosition().y;

	if (lastKey == Keyboard::W && (y - halfHeight) < 0.0f) {
		dirY = 0.0f;
	}
	else if (lastKey == Keyboard::S && (y + halfHeight) > windowPtr->getSize().y) {
		dirY = 0.0f;
	}
	
	float dy = velocity * dirY * time;

	line.move({ 0.0f, dy });
}

void PlayerPanel::Draw()
{
	windowPtr->draw(line);
}

bool PlayerPanel::Contain(Vector2f const& pos) const noexcept
{
	return ((line.getPosition().x - halfWeight) < pos.x && pos.x < (line.getPosition().x + halfWeight))
		&& ((line.getPosition().y - halfHeight) < pos.y && pos.y < (line.getPosition().y + halfHeight));
}

Vector2f PlayerPanel::GetPos() const noexcept
{
	return line.getPosition();
}

unsigned PlayerPanel::GetPoints() const noexcept
{
	return points;
}

void PlayerPanel::IncPoints(unsigned points) noexcept
{
	this->points += points;
}

void PlayerPanel::ResetPoints() noexcept
{
	points = 0;
}