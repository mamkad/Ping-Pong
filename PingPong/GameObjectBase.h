#pragma once

#include <SFML/Graphics.hpp>

using sf::Vector2f;
using std::string;

class GameObjectBase
{
protected:
	unsigned points = 0;

	float velocity = 0.0f;
	float dirX = 0.0f, dirY = 0.0f;

	string name;

public:
	GameObjectBase();

	GameObjectBase(GameObjectBase const&) = delete;
	GameObjectBase(GameObjectBase&&)      = delete;
	GameObjectBase& operator= (GameObjectBase const&) = delete;
	GameObjectBase& operator= (GameObjectBase&&)      = delete;

	virtual ~GameObjectBase();

	virtual bool Contain(Vector2f const& pos) const noexcept = 0;
	virtual Vector2f GetPos()                 const noexcept = 0;

	virtual unsigned GetPoints()      const noexcept = 0;
	virtual void IncPoints(unsigned points) noexcept = 0;
	virtual void ResetPoints()			    noexcept = 0;

	void SetName(string const& name);
	string const& GetName() const noexcept;

	float GetRandomNumber() const noexcept;
};
