#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Scene.h"


class GameScene : public Scene
{
    SDL_Texture* backgroundTexture = nullptr;
    SDL_Texture* background_sheet = nullptr;

	void checkBrickCollisions(float deltaTime);
	void checkBarCollisions(float deltaTime);
	float levelTimer = 0.0f;
	bool paused = false;
    bool endGameBool = false;

	int level = 1;
	int score = 0;

public:
    GameScene();
	~GameScene();
    
    bool init() override;
    
    void start(SDL_Renderer* renderer) override;
    int update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;

    void increaseScore(int points)
    {
        score += points;
        auto scoreText = dynamic_cast<Text*>(entities["scoreText"].get());
        if (scoreText)
            scoreText->setText("SCORE:  " + std::to_string(score));
	}

    void nextLevel(float deltaTime);

    void LoseGame()
    {
        paused = true;
        
	}

    void endGame()
    {
        paused = true;
		menus["endMenu"]->setIsActive(true);
	}
};

