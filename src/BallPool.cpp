#include "BallPool.h"

BallPool::BallPool()
{
	for (int i = 0; i < poolSize; i++)
		balls.push_back(std::make_unique<Ball>());
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
	reset();
	balls[0]->activate(WINDOW_WIDTH / 2 - 8, WINDOW_HEIGHT - 90);
	balls[0]->setGameBall(true);
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
	{
		ball->deactivate();
	}
}

