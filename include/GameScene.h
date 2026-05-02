#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Scene.h"


class GameScene : public Scene
{
    SDL_Texture* backgroundTexture = nullptr;

	void checkBrickCollisions(float deltaTime);
	void checkBarCollisions(float deltaTime);

	int level = 1;
	int score = 0;
	int lives = 3;

public:
    GameScene();
	~GameScene();
    
    bool init() override;
    
    void start(SDL_Renderer* renderer) override;

    
    void update(float deltaTime) override;

    void render(SDL_Renderer* renderer) override;
};

