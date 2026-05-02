#include "Brick.h"

SDL_Texture* Brick::brickTextures[5] = { nullptr };
SDL_Texture* Brick::brickDestroyedTexture = nullptr;

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
	{
		this->type = type;
		this->_type = type;
	}
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
	if (!destroyed)
		return;

	destructionTimer += deltaTime;

	destructionFrame = (int)(destructionTimer / 0.05f);

	if (destructionFrame >= 5)
	{
		active = false;
		destroyed = false;
		destructionFrame = 0;
		destructionTimer = 0.0f;
	}
}

void Brick::render(SDL_Renderer* renderer)
{
	if (!active && !destroyed)
		return;

	SDL_Rect dstRect = {
		(int)transform.x,
		(int)transform.y,
		transform.w,
		transform.h
	};

	if (destroyed)
	{
		SDL_Rect srcRect = {
			160 * destructionFrame,
			0,
			transform.w * 3.32f,
			transform.h * 3.32f
		};

		SDL_RenderCopy(renderer, brickDestroyedTexture, &srcRect, &dstRect);
	}
	else
		SDL_RenderCopy(renderer, brickTextures[type], NULL, &dstRect);
}

bool Brick::destroyBrick()
{
	if(type > 1)
	{
		type--;
		return false;
	}
	active = false;
	destroyed = true;
	return true;
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

	if (!brickDestroyedTexture)
		brickDestroyedTexture = IMG_LoadTexture(renderer, "assets/ExplosionBrick.png");
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
	if(brickDestroyedTexture)
	{
		SDL_DestroyTexture(brickDestroyedTexture);
		brickDestroyedTexture = nullptr;
	}
}