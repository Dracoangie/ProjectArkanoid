#include "Ball.h"

Ball::Ball()
{
    transform.x = WINDOW_WIDTH / 2;
    transform.y = 10;
    transform.w = 16;
    transform.h = 18;
}

Ball::~Ball()
{
}

void Ball::start(SDL_Renderer* renderer)
{
    texture = IMG_LoadTexture(renderer, "assets/Ball.png");
}

void Ball::update(float deltaTime)
{
    if (!active)
        return;
    if (gameBall)
    {
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if ((keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]) && transform.x > 42)
            transform.x -= 400 * deltaTime;
        if ((keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]) && transform.x + transform.w < WINDOW_WIDTH - 43)
            transform.x += 400 * deltaTime;
        if (keystate[SDL_SCANCODE_SPACE])
			gameBall = false;
        else
			return;
    }
	Transform collisionTransform = 
    {
        transform.x + speedX * deltaTime,
        transform.y + speedY * deltaTime,
        transform.w,
		transform.h
    };
    if (CollisionWalls(&collisionTransform))
        speedX = -speedX;
    if (transform.y < 64)
        speedY = -speedY;
    transform.x += speedX * deltaTime;
    transform.y += speedY * deltaTime;
}

void Ball::render(SDL_Renderer* renderer)
{
    if (!active)
        return;
    SDL_Rect transformRect = {
        (int)transform.x,
        (int)transform.y,
        transform.w,
        transform.h
    };
    SDL_RenderCopy(renderer, texture, NULL, &transformRect);
}

void Ball::activate(float x, float y)
{
    transform.x = x;
    transform.y = y;
    resetSpeed();
    active = true;
}

void Ball::activate(float x, float y, float velocityX, float velocityY)
{
    transform.x = x;
    transform.y = y;
    speedX = velocityX;
    speedY = velocityY;
    active = true;
}

void Ball::deactivate()
{
    active = false;
}