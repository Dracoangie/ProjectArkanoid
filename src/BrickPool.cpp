#include "BrickPool.h"

BrickPool::BrickPool()
{
	for (int i = 0; i < poolSize; i++)
		bricks.push_back(std::make_unique<Brick>());
}

BrickPool::~BrickPool()
{
}

void BrickPool::start(SDL_Renderer* renderer)
{
	for (auto& brick : bricks)
		brick->start(renderer);
}

void BrickPool::update(float deltaTime)
{
	for (auto& brick : bricks)
		brick->update(deltaTime);
}

void BrickPool::render(SDL_Renderer* renderer)
{
	for (auto& brick : bricks)
		brick->render(renderer);
}

void BrickPool::reset()
{
	for (auto& brick : bricks)
		brick->active = false;
}
