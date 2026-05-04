#include "StartMenu.h"

StartMenu::StartMenu()
{
	buttons.emplace_back("START", WINDOW_WIDTH / 2 - 100, 310, 1.75f);
	buttons.emplace_back("HOW TO PLAY", WINDOW_WIDTH / 2 - 100, 445, 1.75f);
	buttons.emplace_back("QUIT", WINDOW_WIDTH / 2 - 100, 570, 1.75f);
}

void StartMenu::start(SDL_Renderer* renderer)
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
	if (buttons[2].isClicked())
		return 3; // Quit
	return 0;
}

void StartMenu::render(SDL_Renderer* renderer)
{
	if (!isActive)
		return;
	for (auto& button : buttons)
		button.render(renderer);
}