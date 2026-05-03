#pragma once
#include "Menu.h"

class SelectMenu : public Menu
{
public:
	SelectMenu();

	void start(SDL_Renderer* renderer) override;
	int update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
};
