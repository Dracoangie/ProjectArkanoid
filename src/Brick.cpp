#include "Brick.h"

SDL_Texture* Brick::brickTextures[5] = { nullptr };

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
	Brick::destroyTextures();
}

void Brick::start(SDL_Renderer* renderer)
{
	Brick::loadTextures(renderer);
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
	SDL_RenderCopy(renderer, brickTextures[type], NULL, &transformRect);
}

void Brick::loadTextures(SDL_Renderer* renderer)
{
	if (brickTextures[1] != nullptr)
		return;

	for (int i = 1; i <= 4; i++)
	{
		std::string path = "assets/Brick" + std::to_string(i) + ".png";
		brickTextures[i] = IMG_LoadTexture(renderer, path.c_str());
	}
}

void Brick::destroyTextures()
{
	for (int i = 1; i <= 4; i++)
	{
		if (brickTextures[i])
		{
			SDL_DestroyTexture(brickTextures[i]);
			brickTextures[i] = nullptr;
		}
	}
}