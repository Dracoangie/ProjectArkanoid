#pragma once

#include "Brick.h"
#include "LevelData.h"


class BrickPool : public Entity
{
private:
	std::vector<std::unique_ptr<Brick>> bricks;
	int poolSize = 176;
	int rows = 16;
	int cols = 11;

public:
	BrickPool();
	~BrickPool();

	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	/**
	 * Loads the level data into the brick pool, activating the bricks according to the level layout.
	 * @param levelData A 2D vector representing the level layout, where each integer corresponds to a brick type (0 for no brick).
	 */
	void loadLevel(const std::vector<std::vector<int>>& levelData);
	void reset();

	std::vector<Brick*> getActiveBricks();
};

