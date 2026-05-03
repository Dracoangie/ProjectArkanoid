#include "PowerUpPool.h"

PowerUpPool::PowerUpPool()
{
	for (int i = 0; i < poolSize; i++)
		powerUps.push_back(std::make_unique<PowerUp>(0, 0));
}

PowerUpPool::~PowerUpPool()
{
}

void PowerUpPool::start(SDL_Renderer* renderer)
{
	for (auto& powerUp : powerUps)
		powerUp->start(renderer);
}

void PowerUpPool::update(float deltaTime)
{
	for (auto& powerUp : powerUps)
		powerUp->update(deltaTime);
}

void PowerUpPool::render(SDL_Renderer* renderer)
{
	for (auto& powerUp : powerUps)
		powerUp->render(renderer);
}

void PowerUpPool::spawnPowerUp(float x, float y)
{
	for (auto& powerUp : powerUps)
	{
		if (!powerUp->isActive())
		{
			powerUp->transform.x = x;
			powerUp->transform.y = y;
			powerUp->activate(static_cast<PowerUpType>(rand() % 5));
			return;
		}
	}
}

void PowerUpPool::reset()
{
	for (auto& powerUp : powerUps)
		powerUp->deactivate();
}

void PowerUpPool::deactivatePowerUp(PowerUp* powerUp)
{
	powerUp->deactivate();
}

std::vector<PowerUp*> PowerUpPool::getActivePowerUps()
{
	std::vector<PowerUp*> activePowerUps;
	for (auto& powerUp : powerUps)
	{
		if (powerUp->isActive())
			activePowerUps.push_back(powerUp.get());
	}
	return activePowerUps;
}