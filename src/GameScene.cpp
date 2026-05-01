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
	entities["ballPool"] = std::make_unique<BallPool>();
	entities["bar"] = std::make_unique<Bar>();
	entities["brickPool"] = std::make_unique<BrickPool>();

	return true;
}

void GameScene::start(SDL_Renderer* renderer)
{
	backgroundTexture = IMG_LoadTexture(renderer, "assets/Background.png");
	for (auto& entity : entities)
		entity.second->start(renderer);

	if (entities["brickPool"])
	{
		auto brickPool = dynamic_cast<BrickPool*>(entities["brickPool"].get());
		if (brickPool)
			brickPool->loadLevel(Levels::LEVEL_1);
	}
}
void GameScene::update(float deltaTime)
{
	checkCollisions(deltaTime);
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

void GameScene::checkCollisions(float deltaTime)
{
	auto ballPool = dynamic_cast<BallPool*>(entities["ballPool"].get());
	auto brickPool = dynamic_cast<BrickPool*>(entities["brickPool"].get());

	for (auto& ball : ballPool->getActiveBalls())
	{
		if (!ball->isActive())
			continue;

		for (auto& brick : brickPool->getActiveBricks())
		{
			if (!brick->active)
				continue;

			if (CollisionCheck(&ball->transform, &brick->transform))
			{
				brick->active = false;

				float prevX = ball->transform.x - ball->getSpeedX() * deltaTime;
				float prevY = ball->transform.y - ball->getSpeedY() * deltaTime;

				bool wasAbove = prevY + ball->transform.h <= brick->transform.y;
				bool wasBelow = prevY >= brick->transform.y + brick->transform.h;
				bool wasLeft = prevX + ball->transform.w <= brick->transform.x;
				bool wasRight = prevX >= brick->transform.x + brick->transform.w;

				if (wasAbove || wasBelow)
					ball->setSpeedY(-ball->getSpeedY());
				else if (wasLeft || wasRight)
					ball->setSpeedX(-ball->getSpeedX());
				else
					ball->setSpeedY(-ball->getSpeedY());
				break;
			}
		}
	}
}