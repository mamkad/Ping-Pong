#include "GameObjectBase.h"
#include <iostream>

GameObjectBase::GameObjectBase()
{
	std::cout << "GameObjectBase()\n";
}

GameObjectBase::~GameObjectBase()
{
	std::cout << "~GameObjectBase()\n";
}

unsigned GameObjectBase::Points() const noexcept
{
	return points;
}

void GameObjectBase::AddPoints() noexcept
{
	points += dP;
}

void GameObjectBase::SetName(string const& name)
{
	this->name = name;
}

string const& GameObjectBase::GetName() const noexcept
{
	return name;
}