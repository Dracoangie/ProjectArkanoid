#include "StartScene.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(background_sheet);
}

bool StartScene::init()
{
	menus["startMenu"] = std::make_unique<StartMenu>();
	menus["selectMenu"] = std::make_unique<SelectMenu>();
	menus["howToPlayMenu"] = std::make_unique<HowToPlayMenu>();

	activateOnly("startMenu");

	return true;
}

void StartScene::start(SDL_Renderer* renderer)
{
	backgroundTexture = IMG_LoadTexture(renderer, "assets/Background.png");
	background_sheet = IMG_LoadTexture(renderer, "assets/Background_sheet.png");

	for (auto& menu : menus)
		menu.second->start(renderer);
}

int StartScene::update(float deltaTime)
{
	if (startAnim)
	{
		startChangeSceneTimer(deltaTime);
		return 0;
	}
	if (changingScene)
		return changeSceneTimerUpdate(deltaTime);

	if (waitingMouseRelease)
	{
		int mouseX, mouseY;
		Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

		if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
			return 0;

		waitingMouseRelease = false;
	}

	for (auto& menu : menus)
	{
		int result = menu.second->update(deltaTime);

		if (result == 0)
			continue;

		if (result == 1)
		{
			activateOnly("selectMenu");
			return 0;
		}

		if (result == 2)
		{
			activateOnly("howToPlayMenu");
			return 0;
		}

		if (result == 4)
		{
			activateOnly("startMenu");
			return 0;
		}

		if (result == 3 || result == 10 || result == 11 || result == 12)
		{
			returnValue = result;
			changingScene = true;
			return 0;
		}
	}
	return 0;
}

void StartScene::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	if (backgroundTexture)
		SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	for (auto& menu : menus)
		menu.second->render(renderer);

	if (startAnim || changingScene)
	{
		const int frameCount = 4;
		int changeFrame = (int)(changeSceneTimer * frameCount * 2.5f);
		if (startAnim)
			changeFrame = frameCount - 1 - changeFrame;

		SDL_Rect srcRect = {
			changeFrame * WINDOW_WIDTH,0,
			WINDOW_WIDTH,WINDOW_HEIGHT
		};
		SDL_Rect dstRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };

		SDL_RenderCopy(renderer, background_sheet, &srcRect, &dstRect);
	}

	SDL_RenderPresent(renderer);
}

void StartScene::activateOnly(const std::string& menuName)
{
	for (auto& menu : menus)
		menu.second->setIsActive(false);

	menus[menuName]->setIsActive(true);
	waitingMouseRelease = true;
}