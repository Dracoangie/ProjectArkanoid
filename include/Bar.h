
#pragma once
#include "Entity.h"

class Bar : public Entity
{
	float basicSpeed = 400;
	float speed = 400;

public:
	Bar();
	~Bar();
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void setSpeed(float newSpeed)
	{
		speed = newSpeed;
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
	}

};

