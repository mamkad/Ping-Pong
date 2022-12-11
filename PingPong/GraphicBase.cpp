#pragma once

#include "GraphicBase.h"
#include <iostream>

GraphicBase::GraphicBase(shared_ptr<RenderWindow> const& windowPtr, unsigned id) : windowPtr(windowPtr), id(id)
{
	std::cout << "GraphicBase()\n";
}

GraphicBase::~GraphicBase()
{
	std::cout << "~GraphicBase()\n";
}

unsigned GraphicBase::GetId() const noexcept
{
	return id;
}

Vector2f const& GraphicBase::MousePos() const noexcept
{
	return { float(Mouse::getPosition(*windowPtr).x), float(Mouse::getPosition(*windowPtr).y) };
}
