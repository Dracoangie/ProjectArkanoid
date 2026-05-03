#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{

	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(background_sheet);
}

bool GameScene::init()
{
	entities["ballPool"] = std::make_unique<BallPool>();
	entities["bar"] = std::make_unique<Bar>();
	entities["brickPool"] = std::make_unique<BrickPool>();
	entities["scoreText"] = std::make_unique<Text>("SCORE:  0", 20, 20, 1);
	entities["levelText"] = std::make_unique<Text>("LEVEL:  1", WINDOW_WIDTH /2 + 20, 20, 1);

	menus["endMenu"] = std::make_unique<EndMenu>();

	return true;
}

void GameScene::start(SDL_Renderer* renderer)
{
	for (auto& menu : menus)
		menu.second->start(renderer);
	backgroundTexture = IMG_LoadTexture(renderer, "assets/Background.png");
	background_sheet = IMG_LoadTexture(renderer, "assets/Background_sheet.png");
	for (auto& entity : entities)
		entity.second->start(renderer);

	if (entities["brickPool"])
	{
		auto brickPool = dynamic_cast<BrickPool*>(entities["brickPool"].get());
		if (brickPool)
			brickPool->loadLevel(Levels::LEVEL_1);
	}
}

int GameScene::update(float deltaTime)
{
	if (startAnim)
	{
		startChangeSceneTimer(deltaTime);
		paused = startAnim;
		return 0;
	}
	if (endGameBool)
		return changeSceneTimerUpdate(deltaTime);
	for (auto& menu : menus)
	{
		returnValue = menu.second->update(deltaTime);
		if(returnValue != 0)
		{
			endGameBool = true;
			break;
		}
	}
	if(paused)
		return 0;
	checkBrickCollisions(deltaTime);
	checkBarCollisions(deltaTime);
	for (auto& entity : entities)
		entity.second->update(deltaTime);
	return 0;
}

void GameScene::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer,
		0, 0, 0,
		backgroundColor.a);

	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	for (auto& entity : entities)
		entity.second->render(renderer);

	for (auto& menu : menus)
		menu.second->render(renderer);

	if (startAnim || endGameBool)
	{
		const int frameCount = 4;
		int changeFrame = (int)(changeSceneTimer * frameCount * 2.5f);
		if(startAnim)
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

void GameScene::checkBrickCollisions(float deltaTime)
{
	auto ballPool = dynamic_cast<BallPool*>(entities["ballPool"].get());
	auto brickPool = dynamic_cast<BrickPool*>(entities["brickPool"].get());

	if (levelTimer > 0.0f)
	{
		nextLevel(deltaTime);
		return;
	}
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
		std::vector<Brick*> collidedBricks = brickPool->getActiveBricks();
		if (collidedBricks.empty())
		{
			nextLevel(deltaTime);
			return;
		}
		for (auto& brick : collidedBricks)
		{
			if (!CollisionCheck(&collisionTransform, &brick->transform))
				continue;

			if(brick->destroyBrick())
				increaseScore(brick->getType() * 100);

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
		if (ball->transform.y + ball->transform.h >= WINDOW_HEIGHT)
		{
			ballPool->deactiveBall(ball);
			if(ballPool->getActiveBalls().empty())
				endGame();
		}
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

void GameScene::nextLevel(float deltaTime)
{
	auto ballPool = dynamic_cast<BallPool*>(entities["ballPool"].get());
	auto bar = dynamic_cast<Bar*>(entities["bar"].get());
	if (levelTimer == 0)
	{
		ballPool->reset();
		bar->endLevel();
	}
	levelTimer += deltaTime + 0.0001f;
	if (levelTimer < 1.5f)
		return;
	level++;
	auto levelText = dynamic_cast<Text*>(entities["levelText"].get());
	if (levelText)
		levelText->setText("LEVEL:  " + std::to_string(level));
	if (ballPool)
		ballPool->newLevel();
	if (bar)
		bar->newLevel();
	auto brickPool = dynamic_cast<BrickPool*>(entities["brickPool"].get());
	if (brickPool)
		brickPool->loadLevel(Levels::levels[level - 1]);
	levelTimer = 0.0f;
}