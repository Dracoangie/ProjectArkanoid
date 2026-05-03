#pragma once
#include "Menu.h"
#include "Text.h"

class HowToPlayMenu : public Menu
{
	Text title;
	Text line1;
	Text line2;
	Text line3;
	Text line4;

public:
	HowToPlayMenu();

	void start(SDL_Renderer* renderer) override;
	int update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
};