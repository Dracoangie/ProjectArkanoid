
#pragma once
#include "Entity.h"

class Bar : public Entity
{
	float basicSpeed = 400;
	float speed = basicSpeed;

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
		transform.x = WINDOW_WIDTH / 2 - 40;
		transform.w = 80;
	}

};

