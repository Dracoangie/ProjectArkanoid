
#pragma once
#include "Entity.h"

class Bar : public Entity
{
	SDL_Texture* texture_lose = nullptr;

	float basicSpeed = 400;
	float speed = basicSpeed;
	float loseAnimationTimer = 0.0f;
	bool lose = false;

public:
	Bar();
	Bar(int difficulty);
	~Bar();
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void setSpeed(float newSpeed)
	{
		speed = newSpeed;
	}
	float getSpeed() const
	{
		return speed;
	}
	void resetSpeed()
	{
		speed = basicSpeed;
	}

	void endLevel()
	{
		speed = 0;
	}

	void newLevel()
	{
		resetSpeed();
		lose = false;
		loseAnimationTimer = 0.0f;
		transform.x = WINDOW_WIDTH / 2 - 40;
		transform.w = 80;
	}

	void loseLife()
	{
		lose = true;
	}

};

