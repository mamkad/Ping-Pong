#include "GameObjectBase.h"

#include <random>

GameObjectBase::GameObjectBase()
{
	//std::cout << "GameObjectBase()\n";
}

GameObjectBase::~GameObjectBase()
{
	//std::cout << "~GameObjectBase()\n";
}

void GameObjectBase::SetName(string const& name)
{
	this->name = name;
}

string const& GameObjectBase::GetName() const noexcept
{
	return name;
}

float GameObjectBase::GetRandomNumber() const noexcept
{
	srand((unsigned)time(0));
	return float(rand() % 200) + 50.0f;
}
