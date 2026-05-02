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
	checkBrickCollisions(deltaTime);
	checkBarCollisions(deltaTime);
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

void GameScene::checkBrickCollisions(float deltaTime)
{
	auto ballPool = dynamic_cast<BallPool*>(entities["ballPool"].get());
	auto brickPool = dynamic_cast<BrickPool*>(entities["brickPool"].get());

	for (auto& ball : ballPool->getActiveBalls())
	{
		bool collideX = false;
		bool collideY = false;
		Transform collisionTransform =
		{
			ball->transform.x + ball->getSpeedX() * deltaTime,
			ball->transform.y + ball->getSpeedY() * deltaTime,
			ball->transform.w,
			ball->transform.h
		};

		for (auto& brick : brickPool->getActiveBricks())
		{
			if (!CollisionCheck(&collisionTransform, &brick->transform))
				continue;

			brick->destroyBrick();

			float minOverlapX = std::min(
				(ball->transform.x + ball->transform.w) - brick->transform.x,
				(brick->transform.x + brick->transform.w) - ball->transform.x);
			float minOverlapY = std::min(
				(ball->transform.y + ball->transform.h) - brick->transform.y,
				(brick->transform.y + brick->transform.h) - ball->transform.y);

			if (std::abs(minOverlapX - minOverlapY) <= 1.0f)
			{
				collideX = true;
				collideY = true;
			}
			else if (minOverlapX < minOverlapY)
				collideX = true;
			else
				collideY = true;
		}

		if (collideX)
			ball->setSpeedX(-ball->getSpeedX());
		if (collideY)
			ball->setSpeedY(-ball->getSpeedY());
	}
}

void GameScene::checkBarCollisions(float deltaTime)
{
	auto ballPool = dynamic_cast<BallPool*>(entities["ballPool"].get());
	auto bar = dynamic_cast<Bar*>(entities["bar"].get());

	for (auto& ball : ballPool->getActiveBalls())
	{
		if (ball->getSpeedY() <= 0)
			continue;

		if (CollisionCheck(&ball->transform, &bar->transform))
		{


			float barCenterX = bar->transform.x + bar->transform.w / 2.0f;
			float ballCenterX = ball->transform.x + ball->transform.w / 2.0f;

			float distanceFromCenter = ballCenterX - barCenterX;
			float maxDistance = bar->transform.w / 2.0f;

			float normalizedDistance = distanceFromCenter / maxDistance;
			normalizedDistance = std::max(-1.0f, std::min(1.0f, normalizedDistance));
			normalizedDistance = normalizedDistance * 0.7f;

			float dir = (ball->transform.y + ball->transform.h / 2.0f >
				bar->transform.y + bar->transform.h / 2.0f - 10) ? 1.0f : -1.0f;


			ball->setSpeedX(normalizedDistance * ball->maxSpeed);
			ball->setSpeedY((1 - std::abs(normalizedDistance)) * dir * ball->maxSpeed);
		}
	}
}