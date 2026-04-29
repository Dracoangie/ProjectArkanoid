#include "Game.h"

Game::Game()
{
	if (!init())
		exit(1);

	currentScene = std::make_unique<GameScene>();
	if (!currentScene->init())
		exit(1);
	currentScene->start(renderer);
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
	bool running = true;
	while (running)
	{
		handleEvents();

		currentScene->update();
		currentScene->render(renderer);
	}
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
			exit(0);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			exit(0);
	}
}