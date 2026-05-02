#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Scene.h"


class GameScene : public Scene
{
    SDL_Texture* backgroundTexture = nullptr;

	void checkBrickCollisions(float deltaTime);
	void checkBarCollisions(float deltaTime);
	float levelTimer = 0.0f;

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

    void increaseScore(int points)
    {
        score += points;
        auto scoreText = dynamic_cast<Text*>(entities["scoreText"].get());
        if (scoreText)
            scoreText->setText("SCORE:  " + std::to_string(score));
	}

    void nextLevel(float deltaTime)
    {
        auto ballPool = dynamic_cast<BallPool*>(entities["ballPool"].get());
        auto bar = dynamic_cast<Bar*>(entities["bar"].get());
        if (levelTimer == 0)
        {
            ballPool->reset();
			bar->endLevel();
        }
		levelTimer += deltaTime + 0.0001f;
        if (levelTimer < 1.5f)
            return;
        level++;
        auto levelText = dynamic_cast<Text*>(entities["levelText"].get());
        if (levelText)
            levelText->setText("LEVEL:  " + std::to_string(level));
        if (ballPool)
            ballPool->newLevel();
        if (bar)
            bar->newLevel();
        auto brickPool = dynamic_cast<BrickPool*>(entities["brickPool"].get());
        if (brickPool)
            brickPool->loadLevel(Levels::levels[level - 1]);
		levelTimer = 0.0f;
	}

    void loseLife()
    {
        lives--;
        if (lives <= 0)
        {
            // Game over logic here
            // For now, we just reset the game
            score = 0;
            level = 1;
            auto scoreText = dynamic_cast<Text*>(entities["scoreText"].get());
            if (scoreText)
                scoreText->setText("SCORE:  " + std::to_string(score));
            auto levelText = dynamic_cast<Text*>(entities["levelText"].get());
            if (levelText)
                levelText->setText("LEVEL:  " + std::to_string(level));
            nextLevel(0.0f);
        }
        else
        {
            nextLevel(0.0f);
        }
	}
};

