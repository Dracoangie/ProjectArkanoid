
#pragma once
#include "Entity.h"

class Ball : public Entity
{
public:
	Ball();
	~Ball();
	void start(SDL_Renderer* renderer) override;
	void update() override;
	void render(SDL_Renderer* renderer) override;

};

