#include "SelectMenu.h"

SelectMenu::SelectMenu()
{
	buttons.emplace_back("EASY", WINDOW_WIDTH / 2 - 100, 310, 1.f);
	buttons.emplace_back("NORMAL", WINDOW_WIDTH / 2 - 100, 445, 1.f);
	buttons.emplace_back("HARD", WINDOW_WIDTH / 2 - 100, 570, 1.f);
	buttons.emplace_back("BACK", 450, 685, 0.75f);
}

void SelectMenu::start(SDL_Renderer* renderer)
{
	for (auto& button : buttons)
		button.start(renderer);
	buttons[0].setTextPosition(
		static_cast<float>(WINDOW_WIDTH) / 2 - buttons[0].transform.w / 2.0f, buttons[0].transform.y);
	buttons[1].setTextPosition(
		static_cast<float>(WINDOW_WIDTH) / 2 - buttons[1].transform.w / 2.0f, buttons[1].transform.y);
	buttons[2].setTextPosition(
		static_cast<float>(WINDOW_WIDTH) / 2 - buttons[2].transform.w / 2.0f, buttons[2].transform.y);
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