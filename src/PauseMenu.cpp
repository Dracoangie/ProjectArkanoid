#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
	title = std::make_unique<Text>("PAUSED", 0, 150, 2.0f);
	title->setFont(FontType::Title);
	title->transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - title->transform.w / 2.0f;
	title->setColor({ 146, 232, 192, 255 });
	buttons.emplace_back("RESTART", WINDOW_WIDTH / 2 - 100, 310, 1.f);
	buttons.emplace_back("MAIN MENU", WINDOW_WIDTH / 2 - 100, 375, 1.f);
	buttons.emplace_back("QUIT", WINDOW_WIDTH / 2 - 100, 440, 1.f);
}

void PauseMenu::start(SDL_Renderer* renderer)
{
	title->start(renderer);
	for (auto& button : buttons)
		button.start(renderer);
	buttons[0].setTextPosition(
		static_cast<float>(WINDOW_WIDTH) / 2 - buttons[0].transform.w / 2.0f, buttons[0].transform.y);
	buttons[1].setTextPosition(
		static_cast<float>(WINDOW_WIDTH) / 2 - buttons[1].transform.w / 2.0f, buttons[1].transform.y);
	buttons[2].setTextPosition(
		static_cast<float>(WINDOW_WIDTH) / 2 - buttons[2].transform.w / 2.0f, buttons[2].transform.y);
}

int PauseMenu::update(float deltaTime)
{
	if (!isActive)
		return 0;
	title->update(deltaTime);
	for (auto& button : buttons)
		button.update(deltaTime);
	if (buttons[0].isClicked())
		return 1; // RESTART
	if (buttons[1].isClicked())
		return 2; // MAIN MENU
	if (buttons[2].isClicked())
		return 3; // Quit
	return 0;
}

void PauseMenu::render(SDL_Renderer* renderer)
{
	if (!isActive)
		return;

	SDL_Rect rect = {
	0,
	0,
	WINDOW_WIDTH,
	WINDOW_HEIGHT
	};

	SDL_SetRenderDrawColor(renderer, 40, 44, 60, 100);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &rect);

	title->render(renderer);
	for (auto& button : buttons)
		button.render(renderer);
}