#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

bool GameScene::init()
{
	entities["ball"] = std::make_unique<Ball>();
	entities["bar"] = std::make_unique<Bar>();

	return true;
}

void GameScene::start(SDL_Renderer* renderer)
{
	for (auto& entity : entities)
		entity.second->start(renderer);
}

void GameScene::update(float deltaTime)
{
	for (auto& entity : entities)
		entity.second->update(deltaTime);
}

void GameScene::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 38, 43, 65, 255);
	SDL_RenderClear(renderer);

	for (auto& entity : entities)
		entity.second->render(renderer);

	SDL_RenderPresent(renderer);
}