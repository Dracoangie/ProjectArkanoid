#pragma once
#include "Menu.h"

class StartMenu : public Menu
{
public:
	StartMenu();

	void start(SDL_Renderer* renderer) override;
	int update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
};