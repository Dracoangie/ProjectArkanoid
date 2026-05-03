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
	void checkPowerUpCollisions(float deltaTime);
	float levelTimer = 0.0f;
	bool paused = false;
    bool endGameBool = false;
	int dificulty = 1;
	float slowdownPowerupDuration = 0.0f;
	bool slowdownActive = false;

	int level = 1;
	int score = 0;
	int lives = 2;

public:
    GameScene();
    GameScene(int difficulty);
	~GameScene();
    
    bool init() override;
    
    void start(SDL_Renderer* renderer) override;
    int update(float deltaTime) override;
    void render(SDL_Renderer* renderer) override;

    void increaseScore(int points)
    {
        score += points * dificulty;
        auto scoreText = dynamic_cast<Text*>(entities["scoreText"].get());
        if (scoreText)
            scoreText->setText("SCORE:  " + std::to_string(score));
	}

    void increaseBarWidth(float multiplier)
    {
        auto bar = dynamic_cast<Bar*>(entities["bar"].get());
        if (bar)
            {
            bar->transform.w = static_cast<int>(bar->transform.w * multiplier);
            if (bar->transform.w > 200)
                bar->transform.w = 200;
		}
    }

    void nextLevel(float deltaTime);

    void loseLife()
    {
        lives--;
        if (lives <= 0)
        {
                endGame();
			return;
        }
        dynamic_cast<Bar*>(entities["bar"].get())->newLevel();
        auto ballPool = dynamic_cast<BallPool*>(entities["ballPool"].get());
        ballPool->reset();
		ballPool->newLevel();
    }

    void endGame()
    {
        paused = true;
		menus["endMenu"]->setIsActive(true);
	}

    void setDificulty(int newDificulty)
    {
        dificulty = newDificulty;
	}
    int getDificulty() const
    {
        return dificulty;
	}

	//Powerup functions

    void increaseLife()
    {
        lives++;
    }

    void slowDownBall(float multiplier)
    {
		slowdownActive = true;
        auto ballPool = dynamic_cast<BallPool*>(entities["ballPool"].get());
        if (ballPool)
            ballPool->multiplySpeed(multiplier);
    }

    void extraBall()
    {
        auto ballPool = dynamic_cast<BallPool*>(entities["ballPool"].get());
        if (ballPool)
        {
            for (auto& ball : ballPool->getActiveBalls())
            {
                ballPool->activateBall(
                    ball->transform.x,
                    ball->transform.y - 20);
                ball->setSpeedByDirection((float)(rand() % 360));
            }
        }
	}
};

