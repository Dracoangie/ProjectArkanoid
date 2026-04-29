#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Scene.h"


class GameScene : public Scene
{
    

public:
    GameScene();
	~GameScene();
    
    bool init() override;
    
    void start(SDL_Renderer* renderer) override;

    
    void update(float deltaTime) override;

    void render(SDL_Renderer* renderer) override;
};

