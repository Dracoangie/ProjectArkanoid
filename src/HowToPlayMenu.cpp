#include "HowToPlayMenu.h"

HowToPlayMenu::HowToPlayMenu()
{
	title = Text("HOW TO PLAY", WINDOW_WIDTH / 2 - 120, 120, 2);

	line1 = Text("MOVE THE BAR WITH LEFT AND RIGHT", 60, 240, 1);
	line2 = Text("BOUNCE THE BALL TO DESTROY BRICKS", 60, 290, 1);
	line3 = Text("DO NOT LET THE BALL FALL", 60, 340, 1);
	line4 = Text("DESTROY ALL BRICKS TO WIN", 60, 390, 1);

	buttons.emplace_back("BACK", WINDOW_WIDTH / 2 - 100, 520, 200, 50);
}

void HowToPlayMenu::start(SDL_Renderer* renderer)
{
	title.start(renderer);
	line1.start(renderer);
	line2.start(renderer);
	line3.start(renderer);
	line4.start(renderer);

	for (auto& button : buttons)
		button.start(renderer);
}

int HowToPlayMenu::update(float deltaTime)
{
	if (!isActive)
		return 0;

	for (auto& button : buttons)
		button.update(deltaTime);

	if (buttons[0].isClicked())
		return 4; // Back

	return 0;
}

void HowToPlayMenu::render(SDL_Renderer* renderer)
{
	if (!isActive)
		return;

	title.render(renderer);
	line1.render(renderer);
	line2.render(renderer);
	line3.render(renderer);
	line4.render(renderer);

	for (auto& button : buttons)
		button.render(renderer);
}