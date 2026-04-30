#include "Brick.h"

Brick::Brick()
{
	transform.x = 10;
	transform.y = 10;
	transform.w = 48;
	transform.h = 24;
}

Brick::Brick(int x, int y)
{
	transform.x = x;
	transform.y = y;
	transform.w = 48;
	transform.h = 24;
}

Brick::Brick(int x, int y, int type)
{
	transform.x = x;
	transform.y = y;
	transform.w = 48;
	transform.h = 24;
	if(type > 0 && type < 5)
		this->type = type;
}

Brick::~Brick()
{
	SDL_DestroyTexture(texture);
}

void Brick::start(SDL_Renderer* renderer)
{
	texture = IMG_LoadTexture(renderer, ("assets/Brick" + std::to_string(type) + ".png").c_str());
}

void Brick::update(float deltaTime)
{
}

void Brick::render(SDL_Renderer* renderer)
{
	if(!active)
		return;
	SDL_Rect transformRect = {
		(int)transform.x,
		(int)transform.y,
		transform.w,
		transform.h
	};
	SDL_RenderCopy(renderer, texture, NULL, &transformRect);
}