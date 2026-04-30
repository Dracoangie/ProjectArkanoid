#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"
#include "Ball.h"
#include "Bar.h"
#include <unordered_map>

struct Color
{
	Uint8 r, g, b, a;
};

class Scene
{
protected:
	std::unordered_map<std::string, std::unique_ptr<Entity>> entities;
	Color backgroundColor = { 40, 44, 60, 255 };

public:
	virtual ~Scene() {}

	/**
	 * Initializes the game scene. Returns true if initialization was successful, false otherwise.
	 */
	virtual bool init() = 0;

	/**
	 * Calls the start method of the game objects.
	 */
	virtual void start(SDL_Renderer* renderer) = 0;

	/**
	 * Calls the update method of the game objects.
	 */
	virtual void update(float deltaTime) = 0;

	/**
	 * Calls the render method of the game objects.
	 */
	virtual void render(SDL_Renderer* renderer) = 0;
};

