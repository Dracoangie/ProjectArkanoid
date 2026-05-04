#pragma once
#include "DebugMemory.h"
#include "Entity.h"
#include "Button.h"

class Menu
{
protected:
	bool isActive = false;
	std::vector<Button> buttons;

public:
	virtual ~Menu() {}
	virtual void start(SDL_Renderer* renderer) = 0;
	virtual int update(float deltaTime) = 0;
	virtual void render(SDL_Renderer* renderer) = 0;

	bool getIsActive() const
	{
		return isActive;
	}

	void setIsActive(bool active)
	{
		isActive = active;
	}

};

