#pragma once


#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <map>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

constexpr auto WINDOW_WIDTH = 588;
constexpr auto WINDOW_HEIGHT = 768;


struct Transform
{
	float x, y;
	int w, h;
};

inline bool CollisionCheck(const Transform* a, Transform* b)
{
	return a->x <= b->x + b->w &&
		a->x + a->w >= b->x &&
		a->y <= b->y + b->h &&
		a->y + a->h >= b->y;
}

inline bool CollisionWalls(const Transform* entity)
{
	if (entity->x < 9 || entity->x + entity->w > WINDOW_WIDTH - 9)
		return true;
	return false;
}