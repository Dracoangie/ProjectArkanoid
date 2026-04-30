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
	Transform collisionTransform = 
    {
        transform.x + speedX * deltaTime,
        transform.y + speedY * deltaTime,
        transform.w,
		transform.h
    };
    if (CollisionWalls(&collisionTransform))
        speedX = -speedX;
    if (transform.y < 3)
        speedY = -speedY;
    transform.x += speedX * deltaTime;
    transform.y += speedY * deltaTime;
}

void Ball::render(SDL_Renderer* renderer)
{
    SDL_Rect transformRect = {
        (int)transform.x,
        (int)transform.y,
        transform.w,
        transform.h
    };
    SDL_RenderCopy(renderer, texture, NULL, &transformRect);
}