#include "Bar.h"

Bar::Bar()
{
	transform.x = WINDOW_WIDTH / 2 - 50;
	transform.y = WINDOW_HEIGHT - 50;
	transform.w = 80;
	transform.h = 20;
}

Bar::~Bar()
{
}

void Bar::start(SDL_Renderer* renderer)
{
	texture = IMG_LoadTexture(renderer, "assets/Bar.png");
}

void Bar::update(float deltaTime)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if (keystate[SDL_SCANCODE_LEFT] && transform.x > 10)
		transform.x -= speed * deltaTime;
	if (keystate[SDL_SCANCODE_RIGHT] && transform.x + transform.w < WINDOW_WIDTH - 9)
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