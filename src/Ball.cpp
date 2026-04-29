#include "Ball.h"

Ball::Ball()
{
    transform.x = 0;
    transform.y = 0;
    transform.width = 32;
    transform.height = 32;
}

Ball::~Ball()
{
    SDL_DestroyTexture(texture);
}

void Ball::start(SDL_Renderer* renderer)
{
    texture = IMG_LoadTexture(renderer, "assets/Ball.png");
}

void Ball::update()
{
}

void Ball::render(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}