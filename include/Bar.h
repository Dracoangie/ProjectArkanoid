
#pragma once
#include "Entity.h"

class Bar : public Entity
{
	float speed = 200;

public:
	Bar();
	~Bar();
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

};

