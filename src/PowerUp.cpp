#include "PowerUp.h"


SDL_Texture* PowerUp::powerUpTextures[5] = { nullptr };

PowerUp::PowerUp(int x, int y)
{
	transform.x = x;
	transform.y = y;
	transform.w = 33;
	transform.h = 24;
}

PowerUp::~PowerUp()
{
}

void PowerUp::start(SDL_Renderer* renderer)
{
	PowerUp::loadTextures(renderer);
}

void PowerUp::update(float deltaTime)
{
	if(!active)
		return;
	transform.y += speed * deltaTime;
	if(transform.y > WINDOW_HEIGHT)
		active = false;
}

void PowerUp::render(SDL_Renderer* renderer)
{
	if (!active)
		return;
	SDL_Rect transformRect = {
		(int)transform.x,
		(int)transform.y,
		transform.w,
		transform.h
	};
	SDL_RenderCopy(renderer, powerUpTextures[type], NULL, &transformRect);
}

void PowerUp::loadTextures(SDL_Renderer* renderer)
{
	if (powerUpTextures[0] != nullptr)
		return;

	for (int i = 1; i < 6; i++)
	{
		std::string path = "assets/PowerUp" + std::to_string(i) + ".png";
		powerUpTextures[i - 1] = IMG_LoadTexture(renderer, path.c_str());
	}
}

void PowerUp::destroyTextures()
{
	for (int i = 0; i < 5; i++)
	{
		if (powerUpTextures[i])
		{
			SDL_DestroyTexture(powerUpTextures[i]);
			powerUpTextures[i] = nullptr;
		}
	}
}