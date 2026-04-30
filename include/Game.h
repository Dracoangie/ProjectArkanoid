#pragma once

#include "Scene.h"
#include "Utils.h"
#include <GameScene.h>

class Game
{
	bool running = true;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::shared_ptr<Scene> currentScene;
	std::shared_ptr<Scene> lastScene;

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
	 * Changes the current scene to a new scene. The new scene will be started and rendered in the next iteration of the game loop.
	 */
	void changeScene(std::shared_ptr<Scene> newScene);

	/**
	 * Cleans up resources used by the game, including the SDL window and renderer.
	 */
	void cleanup();

	/**
	 * Handles SDL events, such as quitting the game or pressing the escape key to exit.
	 */
	void handleEvents();

};