#pragma once
#include "Entity.h"
class Brick : public Entity
{
	int type = 1; // 1 for normal brick, 2 for strong brick, etc.
public:
	bool active = true;

	Brick();
	Brick(int x, int y);
	Brick(int x, int y, int type);
	~Brick();

	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	int getType() { return type; }
};

