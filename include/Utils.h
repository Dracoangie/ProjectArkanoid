#pragma once


#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <map>

#include <SDL.h>
#include <SDL_image.h>

constexpr auto WINDOW_WIDTH = 588;
constexpr auto WINDOW_HEIGHT = 768;


struct Transform
{
	float x, y;
	int w, h;
};

inline bool CollisionCheck(Transform* entity1, Transform* entity2)
{
	SDL_Rect rect1 = {
		(int)entity1->x,
		(int)entity1->y,
		entity1->w,
		entity1->h
	};
	SDL_Rect rect2 = {
		(int)entity2->x,
		(int)entity2->y,
		entity2->w,
		entity2->h
	};
	if (SDL_HasIntersection(&rect1, &rect2))
	{
		std::cout << "Collision detected!" << std::endl;
		return true;
	}
	return false;
}

inline bool CollisionWalls(Transform* entity)
{
	if (entity->x < 9 || entity->x + entity->w > WINDOW_WIDTH - 9)
		return true;
	return false;
}