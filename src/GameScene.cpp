#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{

	SDL_DestroyTexture(backgroundTexture);
}

bool GameScene::init()
{
	entities["ball"] = std::make_unique<Ball>();
	entities["bar"] = std::make_unique<Bar>();
	entities["brickPool"] = std::make_unique<BrickPool>();

	return true;
}

void GameScene::start(SDL_Renderer* renderer)
{
	backgroundTexture = IMG_LoadTexture(renderer, "assets/Background.png");
	for (auto& entity : entities)
		entity.second->start(renderer);

	// Load the level data into the brick pool
	if (entities["brickPool"])
	{
		auto brickPool = dynamic_cast<BrickPool*>(entities["brickPool"].get());
		if (brickPool)
			brickPool->loadLevel(Levels::LEVEL_1);
	}
}
void GameScene::update(float deltaTime)
{
	for (auto& entity : entities)
		entity.second->update(deltaTime);
}

void GameScene::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 
		backgroundColor.r,
		backgroundColor.g,
		backgroundColor.b,
		backgroundColor.a);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	for (auto& entity : entities)
		entity.second->render(renderer);

	SDL_RenderPresent(renderer);
}