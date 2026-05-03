#pragma once

#include "Scene.h"
#include "StartMenu.h"
#include "SelectMenu.h"
#include "HowToPlayMenu.h"

class StartScene : public Scene
{
	SDL_Texture* backgroundTexture = nullptr;
	SDL_Texture* background_sheet = nullptr;
	bool changingScene = false;
	bool waitingMouseRelease = false;

	void activateOnly(const std::string& menuName);

public:
	StartScene();
	~StartScene();

	bool init() override;
	void start(SDL_Renderer* renderer) override;
	int update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
};