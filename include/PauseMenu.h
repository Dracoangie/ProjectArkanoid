#pragma once
#include "Menu.h"
class PauseMenu : public Menu
{
	std::unique_ptr<Text> title;
public:
	PauseMenu();
	void start(SDL_Renderer* renderer) override;
	int update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
};

