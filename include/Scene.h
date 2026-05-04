#pragma once

#include "DebugMemory.h"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Utils.h"
#include "Bar.h"
#include "BrickPool.h"
#include "BallPool.h"
#include "Text.h"
#include "LevelData.h"
#include "EndMenu.h"
#include "PowerUpPool.h"
#include <unordered_map>

struct Color
{
	Uint8 r, g, b, a;
};

class Scene
{
protected:
	std::unordered_map<std::string, std::unique_ptr<Entity>> entities;
	std::unordered_map<std::string, std::unique_ptr<Menu>> menus;
	Color backgroundColor = { 40, 44, 60, 255 };
	bool startAnim = true;
	float changeSceneTimer = 0.0f;
	int returnValue = 0;

	void startChangeSceneTimer(float deltaTime)
	{
		changeSceneTimer += deltaTime;
		if (changeSceneTimer >= 0.4f)
		{
			changeSceneTimer = 0.0f;
			startAnim = false;
		}
	}

	int changeSceneTimerUpdate(float deltaTime)
	{
		changeSceneTimer += deltaTime;
		if (changeSceneTimer >= 0.4f)
		{
			changeSceneTimer = 0.0f;
			return returnValue;
		}

		return 0;
	}

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
	virtual int update(float deltaTime) = 0;

	/**
	 * Calls the render method of the game objects.
	 */
	virtual void render(SDL_Renderer* renderer) = 0;
};

