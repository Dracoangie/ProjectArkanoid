#include "EndMenu.h"

EndMenu::EndMenu()
{
	buttons.emplace_back("RESTART", WINDOW_WIDTH / 2 - 75, WINDOW_HEIGHT / 2 - 80, 1.5f);
	buttons.emplace_back("MENU", WINDOW_WIDTH / 2 - 75, WINDOW_HEIGHT / 2 , 1.5f);
	buttons.emplace_back("QUIT", WINDOW_WIDTH / 2 - 75, WINDOW_HEIGHT / 2 + 80, 1.5f);
	buttons[0].transform.y = static_cast<float>(WINDOW_WIDTH) / 2 - buttons[0].transform.w / 2.0f;
	buttons[1].transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - buttons[1].transform.w / 2.0f;
	buttons[2].transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - buttons[2].transform.w / 2.0f;
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