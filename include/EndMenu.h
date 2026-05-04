#pragma once
#include "Menu.h"
#include "Text.h"

class EndMenu : public Menu
{
	std::unique_ptr<Text> title;
public:
	EndMenu();

	void start(SDL_Renderer* renderer) override;
	int update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void lose()
	{
		title->setText("YOU LOSE");
		title->transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - title->transform.w / 2.0f;
		title->setColor({ 251, 196, 167, 255 });
	}


};

