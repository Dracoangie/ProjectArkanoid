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

	entities["ARKANOIDGREEN"] = std::make_unique<Text>("ARKANOID", WINDOW_WIDTH / 2 - 100, 127, 2.0f);
	auto textEntity = dynamic_cast<Text*>(entities["ARKANOIDGREEN"].get());
	textEntity->setFont(FontType::Title);
	textEntity->transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - textEntity->transform.w / 2.0f;
	textEntity->setColor({ 146, 232, 192, 255 });
	entities["ARKANOIDBLUE"] = std::make_unique<Text>("ARKANOID", WINDOW_WIDTH / 2 - 100, 133, 2.0f);
	textEntity = dynamic_cast<Text*>(entities["ARKANOIDBLUE"].get());
	textEntity->setFont(FontType::Title);
	textEntity->transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - textEntity->transform.w / 2.0f;
	textEntity->setColor({ 76, 104, 133, 255 });
	entities["ARKANOID"] = std::make_unique<Text>("ARKANOID", WINDOW_WIDTH / 2 - 100, 130, 2.0f);
	textEntity = dynamic_cast<Text*>(entities["ARKANOID"].get());
	textEntity->setFont(FontType::Title);
	textEntity->transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - textEntity->transform.w / 2.0f;

	activateOnly("startMenu");

	return true;
}

void StartScene::start(SDL_Renderer* renderer)
{
	backgroundTexture = IMG_LoadTexture(renderer, "assets/StartMenu.png");
	background_sheet = IMG_LoadTexture(renderer, "assets/Background_sheet.png");


	for (auto& entity : entities)
		entity.second->start(renderer);
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
	for (auto& entity : entities)
		entity.second->update(deltaTime);
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

	for (auto& entity : entities)
		entity.second->render(renderer);
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