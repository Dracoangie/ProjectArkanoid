#include "EndMenu.h"

EndMenu::EndMenu()
{
	buttons.emplace_back("RESTART", WINDOW_WIDTH / 2 - 75, WINDOW_HEIGHT / 2 - 80, 150, 50);
	buttons.emplace_back("MENU", WINDOW_WIDTH / 2 - 75, WINDOW_HEIGHT / 2 , 150, 50);
	buttons.emplace_back("QUIT", WINDOW_WIDTH / 2 - 75, WINDOW_HEIGHT / 2 + 80, 150, 50);
}

EndMenu::~EndMenu()
{
}

void EndMenu::start(SDL_Renderer* renderer)
{
	for (auto& button : buttons)
		button.start(renderer);
}

int EndMenu::update(float deltaTime)
{
	if(!isActive)
		return 0;
	for (auto& button : buttons)
		button.update(deltaTime);
	if (buttons[0].isClicked())
		return 1; // Restart
	if (buttons[1].isClicked())
		return 2; // Menu
	if (buttons[2].isClicked())
		return 3; // Quit
	return 0;
}

void EndMenu::render(SDL_Renderer* renderer)
{
	if(!isActive)
		return;
	for (auto& button : buttons)
		button.render(renderer);
}