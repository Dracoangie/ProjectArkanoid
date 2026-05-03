#pragma once
#include "Menu.h"
class EndMenu : public Menu
{
	public:
	EndMenu();
	~EndMenu();

	void start(SDL_Renderer* renderer) override;
	int update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;


};

