#include "HowToPlayMenu.h"

HowToPlayMenu::HowToPlayMenu()
{
	lines.emplace_back("MOVE THE BAR WITH LEFT AND RIGHT ARROWS", 60, 290, 0.5f);
	lines.back().setFont(TTF_OpenFont("assets/fonts/04B30.ttf", 15));
	lines.back().transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - lines.back().transform.w / 2.0f;
	lines.emplace_back("OR AD KEYS.", 60, 320, 0.5f);
	lines.back().setFont(TTF_OpenFont("assets/fonts/04B30.ttf", 15));
	lines.back().transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - lines.back().transform.w / 2.0f;
	lines.emplace_back("BOUNCE THE BALL TO DESTROY BRICKS.", 60, 375, 0.5f);
	lines.back().setFont(TTF_OpenFont("assets/fonts/04B30.ttf", 15));
	lines.back().transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - lines.back().transform.w / 2.0f;
	lines.emplace_back("DO NOT LET THE BALL FALL.", 60, 425, 0.5f);
	lines.back().setFont(TTF_OpenFont("assets/fonts/04B30.ttf", 15));
	lines.back().transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - lines.back().transform.w / 2.0f;
	lines.emplace_back("DESTROY ALL BRICKS TO WIN.", 60, 475, 0.5f);
	lines.back().setFont(TTF_OpenFont("assets/fonts/04B30.ttf", 15));
	lines.back().transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - lines.back().transform.w / 2.0f;
	lines.emplace_back("PICK UP THE POWER UPS TO HELP YOU WIN.", 60, 525, 0.5f);
	lines.back().setFont(TTF_OpenFont("assets/fonts/04B30.ttf", 15));
	lines.back().transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - lines.back().transform.w / 2.0f;

	buttons.emplace_back("BACK", 450, 685, 1.0f);
}

void HowToPlayMenu::start(SDL_Renderer* renderer)
{
	for (auto& button : buttons)
		button.start(renderer);

	for(auto& line : lines)
		line.start(renderer);
}

int HowToPlayMenu::update(float deltaTime)
{
	if (!isActive)
		return 0;

	for (auto& button : buttons)
		button.update(deltaTime);

	for (auto& line : lines)
		line.update(deltaTime);

	if (buttons[0].isClicked())
		return 4; // Back

	return 0;
}

void HowToPlayMenu::render(SDL_Renderer* renderer)
{
	if (!isActive)
		return;

	SDL_Rect rect = {
	20,
	250,
	WINDOW_WIDTH - 40,
	400
	};

	SDL_SetRenderDrawColor(renderer,  40, 44, 60, 255 );
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &rect);

	for (auto& button : buttons)
		button.render(renderer);

	for (auto& line : lines)
		line.render(renderer);

}