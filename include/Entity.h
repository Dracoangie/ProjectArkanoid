#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <map>

#include <SDL.h>
#include <SDL_image.h>

struct Transform
{
	int x;
	int y;
	int width;
	int height;
};

class Entity
{
protected:
	SDL_Texture* texture = nullptr;

public:
	Transform transform;

	virtual ~Entity() {}
	virtual void start(SDL_Renderer* renderer) = 0;
	virtual void update() = 0;
	virtual void render(SDL_Renderer* renderer) = 0;

};

