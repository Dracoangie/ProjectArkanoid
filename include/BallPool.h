#pragma once
#include "Ball.h"
#include "Utils.h"

class BallPool : public Entity
{
private:
	std::vector<std::unique_ptr<Ball>> balls;
	int poolSize = 5;

	void activateBall(float x, float y);

	/**
	 * Resets the ball pool, deactivating all balls and resetting their positions.
	 */
	void reset();

public:
	BallPool();
	~BallPool();
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void newLevel();
	std::vector<Ball*> getActiveBalls();
};

