#include "GameScene.h"

GameScene::GameScene()
{
	press = std::make_unique<Text>("PRESS SPACE TO START", WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 200, 1.0f);
	press->setFont(TTF_OpenFont("assets/fonts/04B30.ttf", 24));
	press->transform.x = static_cast<float>(WINDOW_WIDTH) / 2 - press->transform.w / 2.0f;
	press->setColor({ 255, 255, 255, 100 });

}

GameScene::~GameScene()
{
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(backgroundBreakthroughTexture);
	SDL_DestroyTexture(background_sheet);
}

GameScene::GameScene(int difficulty) : GameScene()
{
	dificulty = difficulty;
}

bool GameScene::init()
{
	loadHighScore();

	entities["bar"] = std::make_unique<Bar>(dificulty);

	entities["ballPool"] = std::make_unique<BallPool>(dificulty);
	entities["brickPool"] = std::make_unique<BrickPool>();
	entities["powerUpPool"] = std::make_unique<PowerUpPool>();

	entities["scoreText"] = std::make_unique<Text>("SCORE:  0", 20, 20, 1);
	entities["levelText"] = std::make_unique<Text>("LEVEL:  1", WINDOW_WIDTH /2 + 35, 14, 1);
	dynamic_cast<Text*>(entities["levelText"].get())->setFont(TTF_OpenFont("assets/fonts/DePixelHalbfett.ttf", 15));
	entities["LivesText"] = std::make_unique<Text>("LIVES:  2", WINDOW_WIDTH / 2 + 170, 14, 1);
	dynamic_cast<Text*>(entities["LivesText"].get())->setFont(TTF_OpenFont("assets/fonts/DePixelHalbfett.ttf", 15));
	entities["highText"] = std::make_unique<Text>("HIGH SCORE:  " + std::to_string(highScore), WINDOW_WIDTH / 2 + 35, 43, 1);
	dynamic_cast<Text*>(entities["highText"].get())->setFont(TTF_OpenFont("assets/fonts/DePixelHalbfett.ttf", 9));

	menus["endMenu"] = std::make_unique<EndMenu>();
	menus["pauseMenu"] = std::make_unique<PauseMenu>();

	return true;
}

void GameScene::start(SDL_Renderer* renderer)
{
	backgroundTexture = IMG_LoadTexture(renderer, "assets/Background.png");
	backgroundBreakthroughTexture = IMG_LoadTexture(renderer, "assets/BackGroundBreak.png");
	background_sheet = IMG_LoadTexture(renderer, "assets/Background_sheet.png");

	for (auto& menu : menus)
		menu.second->start(renderer);
	for (auto& entity : entities)
		entity.second->start(renderer);
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
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	bool escapePressed = keystate[SDL_SCANCODE_ESCAPE];

	if (escapePressed && !escapeWasPressed)
	{
		paused = !paused;
		menus["pauseMenu"]->setIsActive(paused);
	}
	escapeWasPressed = escapePressed;
	if (paused)
		return 0;
	checkBrickCollisions(deltaTime);
	checkBarCollisions(deltaTime);
	checkPowerUpCollisions(deltaTime);
	if(breakthroughActive)
	{
		auto bar = dynamic_cast<Bar*>(entities["bar"].get());
		if(bar->transform.x + bar->transform.w >= WINDOW_WIDTH - 20)
			nextLevel(deltaTime);

	}
	if(slowdownActive)
	{
		slowdownPowerupDuration += deltaTime;
		if(slowdownPowerupDuration >= 5.0f)
		{
			slowdownActive = false;
			auto ballPool = dynamic_cast<BallPool*>(entities["ballPool"].get());
			if (ballPool)
				ballPool->resetSpeed();
			slowdownPowerupDuration = 0.0f;
		}
	}
	for (auto& entity : entities)
		entity.second->update(deltaTime);
	if (keystate[SDL_SCANCODE_SPACE])
		pressed = true;
	return 0;
}

void GameScene::render(SDL_Renderer* renderer)
{

	SDL_SetRenderDrawColor(renderer,
		0, 0, 0,
		backgroundColor.a);

	SDL_RenderClear(renderer);

	if(breakthroughActive)
		SDL_RenderCopy(renderer, backgroundBreakthroughTexture, NULL, NULL);
	else
		SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

	if (!pressed)
		press->render(renderer);

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
	auto powerUpPool = dynamic_cast<PowerUpPool*>(entities["powerUpPool"].get());

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
			ball->multiplySpeed(1.02f);

			if(rand() % 100 < 20)
				powerUpPool->spawnPowerUp(brick->transform.x, brick->transform.y);

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
				loseLife();
		}
		if(breakthroughActive)
		{
			breakthroughPowerupDuration += deltaTime;
			if(breakthroughPowerupDuration >= 3.0f)
			{
				breakthroughActive = false;
				breakthroughPowerupDuration = 0.0f;
			}
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

void GameScene::checkPowerUpCollisions(float deltaTime)
{
	auto powerUpPool = dynamic_cast<PowerUpPool*>(entities["powerUpPool"].get());
	auto bar = dynamic_cast<Bar*>(entities["bar"].get());
	for (auto& powerUp : powerUpPool->getActivePowerUps())
	{
		if (!CollisionCheck(&powerUp->transform, &bar->transform))
			continue;
		switch (powerUp->getType())
		{
			case PowerUpType::Expand:
				increaseBarWidth(1.5f);
				break;
			case PowerUpType::ExtraLife:
				increaseLife();
				break;
			case PowerUpType::SpeedDown:
				slowDownBall(0.7f);
				break;
			case PowerUpType::ExtraBall:
				extraBall();
				break;
			case PowerUpType::Breakthrough:
				breakthroughActive = true;
				break;
			default:
				break;
		}
		powerUp->deactivate();
	}
}

void GameScene::nextLevel(float deltaTime)
{
	breakthroughActive = false;
	auto ballPool = dynamic_cast<BallPool*>(entities["ballPool"].get());
	auto powerUpPool = dynamic_cast<PowerUpPool*>(entities["powerUpPool"].get());
	auto bar = dynamic_cast<Bar*>(entities["bar"].get());
	if (levelTimer == 0)
	{
		ballPool->reset();
		powerUpPool->reset();
		bar->endLevel();
	}
	levelTimer += deltaTime + 0.0001f;
	if (levelTimer < 1.5f)
		return;
	level++;
	auto levelText = dynamic_cast<Text*>(entities["levelText"].get());
	if (bar)
		bar->newLevel();
	if (ballPool)
		ballPool->newLevel();
	auto brickPool = dynamic_cast<BrickPool*>(entities["brickPool"].get());
	if (brickPool)
	{
		if (level > Levels::levels.size())
		{
			 endGame();
			 return;
		}
		brickPool->loadLevel(Levels::levels[level - 1]);
	}
	if (levelText)
		levelText->setText("LEVEL:  " + std::to_string(level));
	levelTimer = 0.0f;
}