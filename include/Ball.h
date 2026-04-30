
#pragma once
#include "Entity.h"

class Ball : public Entity
{
	float speedX = 200;
	float speedY = 200;

public:
	Ball();
	~Ball();
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

};

