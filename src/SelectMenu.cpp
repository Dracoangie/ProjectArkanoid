#include "SelectMenu.h"

SelectMenu::SelectMenu()
{
	buttons.emplace_back("EASY", WINDOW_WIDTH / 2 - 100, 240, 200, 50);
	buttons.emplace_back("NORMAL", WINDOW_WIDTH / 2 - 100, 320, 200, 50);
	buttons.emplace_back("HARD", WINDOW_WIDTH / 2 - 100, 400, 200, 50);
	buttons.emplace_back("BACK", WINDOW_WIDTH / 2 - 100, 500, 200, 50);
}

void SelectMenu::start(SDL_Renderer* renderer)
{
	for (auto& button : buttons)
		button.start(renderer);
}

int SelectMenu::update(float deltaTime)
{
	if (!isActive)
		return 0;
	for (auto& button : buttons)
		button.update(deltaTime);
	if (buttons[0].isClicked())
		return 10; // Easy
	else if (buttons[1].isClicked())
		return 11; // Normal
	else if (buttons[2].isClicked())
		return 12; // Hard
	else if (buttons[3].isClicked())
		return 4; // Back
	return 0;
}

void SelectMenu::render(SDL_Renderer* renderer)
{
	if (!isActive)
		return;
	for (auto& button : buttons)
		button.render(renderer);
}