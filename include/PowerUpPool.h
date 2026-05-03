#pragma once
#include "Entity.h"
#include "PowerUp.h"


class PowerUpPool : public Entity
{
	static const int poolSize = 20;
	std::vector<std::unique_ptr<PowerUp>> powerUps;

public:
	PowerUpPool();
	~PowerUpPool();
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
	void spawnPowerUp(float x, float y);
	void reset();
	void deactivatePowerUp(PowerUp* powerUp);
	std::vector<PowerUp*> getActivePowerUps();

};

