#pragma once
#include "Menu.h"
#include "Text.h"

class HowToPlayMenu : public Menu
{
	std::vector<Text> lines;

public:
	HowToPlayMenu();

	void start(SDL_Renderer* renderer) override;
	int update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
};