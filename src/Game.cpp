#include "Game.h"

Game::Game()
{
	if (!init())
		exit(1);

	lastScene = nullptr;
	currentScene = std::make_shared<GameScene>();
	if (!currentScene->init())
		exit(1);
}

Game::~Game()
{
	cleanup();
}

bool Game::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		return false;
	if(TTF_Init())
		return false;
	window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window)
		return false;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
		return false;
	return true;
}

void Game::run()
{
	Uint64 lastTime = SDL_GetTicks64();
	while (running)
	{
		Uint64 currentTime = SDL_GetTicks64();
		float deltaTime = (currentTime - lastTime) / 1000.0f;
		lastTime = currentTime;
		handleEvents();

		if (currentScene != lastScene)
		{
			currentScene->start(renderer);
			lastScene = currentScene;
		}

		currentScene->update(deltaTime);
		currentScene->render(renderer);
	}
}

void Game::changeScene(std::shared_ptr<Scene> newScene)
{
	currentScene = newScene;
}

void Game::cleanup()
{
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			running = false;
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			running = false;
	}
}