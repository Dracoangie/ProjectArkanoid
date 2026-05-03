#include "StartMenu.h"

StartMenu::StartMenu()
{
	buttons.emplace_back("START", WINDOW_WIDTH / 2 - 100, 240, 200, 50);
	buttons.emplace_back("HOW TO PLAY", WINDOW_WIDTH / 2 - 100, 320, 200, 50);
}

void StartMenu::start(SDL_Renderer* renderer)
{
	for (auto& button : buttons)
		button.start(renderer);
}

int StartMenu::update(float deltaTime)
{
	if (!isActive)
		return 0;
	for (auto& button : buttons)
		button.update(deltaTime);
	if (buttons[0].isClicked())
		return 1; // Start
	if (buttons[1].isClicked())
		return 2; // How to play
	return 0;
}

void StartMenu::render(SDL_Renderer* renderer)
{
	if (!isActive)
		return;
	for (auto& button : buttons)
		button.render(renderer);
}