
#pragma once
#include "Entity.h"

class Ball : public Entity
{
	static float basicspeed;
	float speedX = 0;
	float speedY = -basicspeed;
	bool active = false;
	bool gameBall = false;
	float gameBallSpeed;

	void resetSpeed()
	{
		int randir = rand() % 2 == 0 ? -1 : 1;
		int ran = rand() % 100;
		speedX = ran * randir; speedY = -basicspeed + ran; maxSpeed = basicspeed;
	}
public:
	float maxSpeed = basicspeed;
	Ball();
	~Ball();
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void resetMovement()
	{
		speedX = speedX * (basicspeed / maxSpeed);
		speedY = speedY * (basicspeed / maxSpeed);
		maxSpeed = basicspeed;
	}

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

	void setGameBall(bool value, int speed) { gameBall = value; gameBallSpeed = (float)speed; }
	bool getGameBall() const { return gameBall; }
	float getSpeedX() const { return speedX; }
	float getSpeedY() const { return speedY; }
	void setSpeedX(float newSpeedX) { speedX = newSpeedX; }
	void setSpeedY(float newSpeedY) { speedY = newSpeedY; }
	void setSpeedByDirection(float angleDegrees)
	{
		float angleRadians = angleDegrees * 3.14159265f / 180.0f;
		speedX = maxSpeed * cos(angleRadians);
		speedY = maxSpeed * sin(angleRadians);
	}
};