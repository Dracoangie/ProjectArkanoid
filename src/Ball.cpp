#include "Ball.h"

Ball::Ball()
{
    transform.x = 0;
    transform.y = 0;
    transform.w = 16;
    transform.h = 18;
}

Ball::~Ball()
{
    SDL_DestroyTexture(texture);
}

void Ball::start(SDL_Renderer* renderer)
{
    texture = IMG_LoadTexture(renderer, "assets/Ball.png");
}

void Ball::update(float deltaTime)
{
    transform.x += speed * deltaTime;
    transform.y += speed * deltaTime;
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