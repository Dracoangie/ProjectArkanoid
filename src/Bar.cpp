#include "Bar.h"

Bar::Bar()
{
	transform.x = 600;
	transform.y = 700;
	transform.w = 100;
	transform.h = 40;
}

Bar::~Bar()
{
	SDL_DestroyTexture(texture);
}

void Bar::start(SDL_Renderer* renderer)
{
	texture = IMG_LoadTexture(renderer, "assets/Bar.png");
}

void Bar::update(float deltaTime)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_LEFT])
		transform.x -= speed * deltaTime;
	if (keystate[SDL_SCANCODE_RIGHT])
		transform.x += speed * deltaTime;
}

void Bar::render(SDL_Renderer* renderer)
{
	SDL_Rect transformRect = {
		(int)transform.x,
		(int)transform.y,
		transform.w,
		transform.h
	};
	SDL_RenderCopy(renderer, texture, NULL, &transformRect);
}