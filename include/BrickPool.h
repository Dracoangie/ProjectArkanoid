#pragma once

#include "Brick.h"


class BrickPool : public Entity
{
private:
	std::vector<std::unique_ptr<Brick>> bricks;
	int poolSize = 176;

public:
	BrickPool();
	~BrickPool();

	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void reset();
};

