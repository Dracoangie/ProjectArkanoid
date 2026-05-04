#include "Bar.h"

Bar::Bar()
{
	transform.x = WINDOW_WIDTH / 2 - 40;
	transform.y = WINDOW_HEIGHT - 50;
	transform.w = 80;
	transform.h = 20;
}

Bar::Bar(int difficulty) : Bar()
{
	basicSpeed *= 1.0f + 0.5f * (difficulty - 1);
	resetSpeed();
}

Bar::~Bar()
{
	if (texture_lose)
		SDL_DestroyTexture(texture_lose);
}

void Bar::start(SDL_Renderer* renderer)
{
	texture = IMG_LoadTexture(renderer, "assets/Bar.png");
	texture_lose = IMG_LoadTexture(renderer, "assets/Bar_Lose.png");
}

void Bar::update(float deltaTime)
{
	if (lose)
	{
		loseAnimationTimer += deltaTime;
		return;
	}

	const Uint8* keystate = SDL_GetKeyboardState(NULL);
	if ((keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]) && transform.x > 10)
		transform.x -= speed * deltaTime;
	if ((keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]) && transform.x + transform.w < WINDOW_WIDTH - 9)
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

	if (lose)
	{
		int destructionFrame = (int)(loseAnimationTimer / 0.1f);
		SDL_Rect srcRect = {
			destructionFrame* 60, 0,
			60, transform.h
		};
		SDL_RenderCopy(renderer, texture_lose, &srcRect, &transformRect);
		return;
	}
	SDL_RenderCopy(renderer, texture, NULL, &transformRect);
}