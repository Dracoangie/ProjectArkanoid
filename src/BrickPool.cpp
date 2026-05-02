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

void BrickPool::loadLevel(const std::vector<std::vector<int>>& levelData)
{
	reset();
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < cols; col++)
		{
			int index = row * cols + col;
			if (index < poolSize)
			{
				bricks[index]->transform.x = 15 +col * 51;
				bricks[index]->transform.y = 75 + row * 24;
				bricks[index]->active = levelData[row][col] > 0;
				if (levelData[row][col] > 0)
					bricks[index]->setType(levelData[row][col]);
				else
					bricks[index]->active = false;
			}
		}
	}
}

void BrickPool::reset()
{
	for (auto& brick : bricks)
		brick->active = true;
}

std::vector<Brick*> BrickPool::getActiveBricks()
{
	std::vector<Brick*> activeBricks;
	for (auto& brick : bricks)
	{
		if (brick->active && !brick->isDestroyed())
			activeBricks.push_back(brick.get());
	}
	return activeBricks;
}
