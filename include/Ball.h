
#pragma once
#include "Entity.h"

class Ball : public Entity
{
	static const int basicspeedX = 400;
	static const int basicspeedY = 400;
	float speedX = basicspeedX;
	float speedY = basicspeedY;
	bool active = false;
	bool gameBall = false;

	void resetSpeed() { speedX = 0; speedY = -basicspeedY; }
public:
	Ball();
	~Ball();
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void multiplySpeed(float multiplier) { speedX *= multiplier; speedY *= multiplier; }

	bool isActive() const { return active; }
	void activate(float x, float y);
	void activate(float x, float y, float velocityX, float velocityY);
	void deactivate();

	void setGameBall(bool value) { gameBall = value; }
	float getSpeedX() const { return speedX; }
	float getSpeedY() const { return speedY; }
	void setSpeedX(float newSpeedX) { speedX = newSpeedX; }
	void setSpeedY(float newSpeedY) { speedY = newSpeedY; }
};

