#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Scene.h"


class GameScene : public Scene
{
    SDL_Texture* backgroundTexture = nullptr;

	void checkCollisions(float deltaTime);

public:
    GameScene();
	~GameScene();
    
    bool init() override;
    
    void start(SDL_Renderer* renderer) override;

    
    void update(float deltaTime) override;

    void render(SDL_Renderer* renderer) override;
};

