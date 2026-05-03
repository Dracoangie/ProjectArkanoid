#pragma once
#include "Ball.h"
#include "Utils.h"

class BallPool : public Entity
{
private:
	std::vector<std::unique_ptr<Ball>> balls;
	int poolSize = 5;
	int difficulty = 1;

public:
	BallPool(int difficulty);
	~BallPool();
	void activateBall(float x, float y);
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void reset();
	void newLevel();
	std::vector<Ball*> getActiveBalls();
	void multiplySpeed(float multiplier);
	void resetSpeed()
	{
		for (auto& ball : balls)
			ball->resetMovement();
	}
	void deactiveBall(Ball* ball);
	void multiplyBasicSpeed(int difficulty)
	{
		Ball::multiplyBasicSpeed(difficulty);
	}
};

