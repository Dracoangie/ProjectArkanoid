
#pragma once
#include "Entity.h"

class Ball : public Entity
{
	static int basicspeed;
	float speedX = 0;
	float speedY = -basicspeed;
	bool active = false;
	bool gameBall = false;
	float gameBallSpeed;

	void resetSpeed()
	{
		speedX = 0; speedY = -basicspeed; maxSpeed = basicspeed;
		std::cout << "Resetting ball speed to: " << speedX << ", " << speedY << std::endl;
	}
public:
	float maxSpeed = basicspeed;
	Ball();
	~Ball();
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void multiplySpeed(float multiplier)
	{ 
		speedX *= multiplier; speedY *= multiplier; 
		maxSpeed *= multiplier;
	}

	static void multiplyBasicSpeed(int difficulty)
	{
		basicspeed = 500;
		basicspeed *= 1.0f + 0.25f * (difficulty - 1);
	}

	bool isActive() const { return active; }
	void activate(float x, float y);
	void activate(float x, float y, float velocityX, float velocityY);
	void deactivate();

	void setGameBall(bool value, int speed) { gameBall = value; gameBallSpeed = speed; }
	float getSpeedX() const { return speedX; }
	float getSpeedY() const { return speedY; }
	void setSpeedX(float newSpeedX) { speedX = newSpeedX; }
	void setSpeedY(float newSpeedY) { speedY = newSpeedY; }
};