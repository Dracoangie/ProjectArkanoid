#include "BallPool.h"

BallPool::BallPool(int difficulty) : difficulty(difficulty)
{
	for (int i = 0; i < poolSize; i++)
		balls.push_back(std::make_unique<Ball>());
	multiplyBasicSpeed(difficulty);
}

BallPool::~BallPool()
{
}

void BallPool::start(SDL_Renderer* renderer)
{
	newLevel();
	for (auto& ball : balls)
		ball->start(renderer);
}

void BallPool::update(float deltaTime)
{
	for (auto& ball : balls)
		ball->update(deltaTime);
}

void BallPool::render(SDL_Renderer* renderer)
{
	for (auto& ball : balls)
		ball->render(renderer);
}

void BallPool::newLevel()
{
	balls[0]->activate(WINDOW_WIDTH / 2 - 8, WINDOW_HEIGHT - 70);
	balls[0]->setGameBall(true, (int)(400 * (1.0f + 0.5f * (difficulty - 1))));
}

std::vector<Ball*> BallPool::getActiveBalls()
{
	std::vector<Ball*> activeBalls;
	for (auto& ball : balls)
	{
		if (ball->isActive())
			activeBalls.push_back(ball.get());
	}
	return activeBalls;
}

void BallPool::activateBall(float x, float y)
{
	for (auto& ball : balls)
	{
		if (!ball->isActive())
		{
			ball->activate(x, y);
			break;
		}
	}
}

void BallPool::reset()
{
	for (auto& ball : balls)
		ball->deactivate();
}

void BallPool::multiplySpeed(float multiplier)
{
	for (auto& ball : balls)
	{
		if (ball->isActive())
			ball->multiplySpeed(multiplier);
	}
}

void BallPool::deactiveBall(Ball* ball)
{
	ball->deactivate();
}

