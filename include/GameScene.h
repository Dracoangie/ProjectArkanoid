#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Scene.h"
#include "PauseMenu.h"
#include <fstream>

class GameScene : public Scene
{
	std::unique_ptr<Text> press;
	bool pressed = false;
    SDL_Texture* backgroundTexture = nullptr;
    SDL_Texture* backgroundBreakthroughTexture = nullptr;
    SDL_Texture* background_sheet = nullptr;
	int highScore = 0;

    int dificulty = 1;

	bool paused = false;
    bool escapeWasPressed = false;
    bool endGameBool = false;
    bool losingLife = false;
    float losingLifeTimer = 0.0f;

    float levelTimer = 0.0f;

	float slowdownPowerupDuration = 0.0f;
	bool slowdownActive = false;

    float breakthroughPowerupDuration = 0.0f;
    bool breakthroughActive = false;

	int score = 0;
    int level = 1;
	int lives = 2;

    void checkBrickCollisions(float deltaTime);
    void checkBarCollisions(float deltaTime);
    void checkPowerUpCollisions(float deltaTime);


    void saveHighScore()
    {
        std::ofstream file("highscore.txt");

        if (file.is_open())
        {
            file << highScore;
            file.close();
        }
    }

    void loadHighScore()
    {
        std::ifstream file("highscore.txt");

        if (file.is_open())
        {
            file >> highScore;
            file.close();
        }
        else
            highScore = 0;
    }
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
        if(score > highScore)
        {
            highScore = score;
            auto highText = dynamic_cast<Text*>(entities["highText"].get());
            if (highText)
                highText->setText("HIGH SCORE:  " + std::to_string(highScore));
        }
    }

    void nextLevel(float deltaTime);

    void loseLife()
    {
        lives--;
        if (lives <= 0)
        {
            endGame(true);
			return;
        }
        dynamic_cast<Bar*>(entities["bar"].get())->newLevel();
        auto ballPool = dynamic_cast<BallPool*>(entities["ballPool"].get());
        ballPool->reset();
		ballPool->newLevel();

        dynamic_cast<Text*>(entities["LivesText"].get())->setText("LIVES:  " + std::to_string(lives));
    }

    void endGame(bool lose)
    {
        breakthroughPowerupDuration = 0;
        paused = true;
		menus["endMenu"]->setIsActive(true);
		if (lose)
			dynamic_cast<EndMenu*>(menus["endMenu"].get())->lose();
		dynamic_cast<BrickPool*>(entities["brickPool"].get())->deactivateAllBricks();
        saveHighScore();
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

    void increaseBarWidth(float multiplier)
    {
        auto bar = dynamic_cast<Bar*>(entities["bar"].get());

        if (!bar)
            return;

        float oldWidth = bar->transform.w;
        float newWidth = oldWidth * multiplier;

        if (newWidth > 200)
            newWidth = 200;

        float delta = newWidth - oldWidth;
        bar->transform.x -= delta / 2.0f;
        bar->transform.w = newWidth;
    }

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

