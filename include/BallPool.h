#pragma once
#include "Ball.h"
#include "Utils.h"

class BallPool : public Entity
{
private:
	std::vector<std::unique_ptr<Ball>> balls;
	int poolSize = 5;

	void activateBall(float x, float y);

public:
	BallPool();
	~BallPool();
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void reset();
	void newLevel();
	std::vector<Ball*> getActiveBalls();
};

