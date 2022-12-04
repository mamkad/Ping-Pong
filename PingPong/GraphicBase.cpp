#pragma once

#include "GraphicBase.h"
#include <iostream>

GraphicBase::GraphicBase(shared_ptr<RenderWindow> const& windowPtr) : windowPtr_(windowPtr)
{
	std::cout << "GraphicBase()\n";
}

GraphicBase::~GraphicBase()
{
	std::cout << "~GraphicBase()\n";
}
