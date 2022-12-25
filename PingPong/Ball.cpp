#include "Ball.h"

Ball::Ball(shared_ptr<RenderWindow> const& windowPtr, unsigned id) : GraphicBase(windowPtr, id)
{
	//std::cout << "Ball()\n";
}

Ball::~Ball()
{
	//std::cout << "~Ball()\n";
}

void Ball::Init(ifstream& cfgFile)
{
	float radius, ballX, ballY;
	unsigned bR, bG, bB, bOR, bOG, bOB;
	float thicknes, pintCount;

	if (!(cfgFile >> name >> radius >> pintCount >> ballX >> ballY
		>> bR >> bG >> bB >> thicknes >> bOR >> bOG >> bOB
			>> points >> velocity >> dirX >> dirY
				>> countOfReflectionsThatIncreaseVelocity >> dVelocity)) {

		throw invalid_argument("Error of init Ball class");
	}
	circle.setPointCount(500);
	circle.setRadius(radius);
	circle.setOrigin(radius, radius);
	circle.setPosition(ballX, ballY);
	circle.setFillColor(Color(bR, bG, bB));
	circle.setOutlineThickness(thicknes);
	circle.setOutlineColor(Color(bOR, bOG, bOB));

	startVelocity = velocity;
}

void Ball::Control(Event const& event)
{
}

void Ball::Update(float time)
{
	float y = circle.getPosition().y;

	if (y + circle.getRadius() > windowPtr->getSize().y) {
		dirY = -1.0f;
	}
	else if (y - circle.getRadius() < 0.0f) {
		dirY = 1.0f;
	}
	
	float dx = velocity * dirX * time, dy = velocity * dirY * time;

	circle.move({ dx, dy });
}

void Ball::Draw()
{
	windowPtr->draw(circle);
}

bool Ball::Contain(Vector2f const& pos) const noexcept
{
	return (fabs(circle.getPosition().x - pos.x) < circle.getRadius()) && (fabs(circle.getPosition().y - pos.y) < circle.getRadius());
}


void Ball::SetPos(Vector2f const& pos)
{
	circle.setPosition(pos);
}

Vector2f Ball::GetPos() const noexcept
{
	//float angle = cosf(45 * 3.14f / 180.0f);
	return (dirX > 0.0f) ? Vector2f(circle.getPosition().x + circle.getRadius(), circle.getPosition().y  ) : Vector2f(circle.getPosition().x - circle.getRadius(), circle.getPosition().y);
	//return { circle.getPosition().x + circle.getRadius() * dirX * angle , circle.getPosition().y + circle.getRadius() * dirY * angle };
}

void Ball::SetDirs(float dirX, float dirY)
{
	this->dirX = dirX;

	if (dirY > 0) {
		this->dirY = dirY;
	}
}

unsigned Ball::GetPoints() const noexcept
{
	return points;
}

void Ball::IncPoints(unsigned points) noexcept
{
	this->points += points;

	if (!(points % countOfReflectionsThatIncreaseVelocity)) {
		velocity += dVelocity;
	}
}

void Ball::ResetPoints() noexcept
{
	points = 0;
	velocity = startVelocity;
}


