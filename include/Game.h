#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "Scene.h"
#include <GameScene.h>

constexpr auto WINDOW_WIDTH = 800;
constexpr auto WINDOW_HEIGHT = 600;

class Game
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::unique_ptr<Scene> currentScene;

public:
	Game();
	~Game();
	/**
	 * Initialice the SDL library, create the game window and renderer. Returns true if initialization was successful, false otherwise.
	 */
	bool init();

	/**
	 * Starts the main game loop, which continues until the game is closed. Inside the loop, it handles events, updates the current scene and renders it.
	 */
	void run();

	/**
	 * Cleans up resources used by the game, including the SDL window and renderer.
	 */
	void cleanup();

	/**
	 * Handles SDL events, such as quitting the game or pressing the escape key to exit.
	 */
	void handleEvents();

};