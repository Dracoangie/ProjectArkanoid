#pragma once
#include "Entity.h"


enum PowerUpType
{
	Expand,
	SpeedDown,
	ExtraLife,
	ExtraBall,
	Breakthrough
};

class PowerUp : public Entity
{
	static  SDL_Texture* powerUpTextures[5];
	int speed = 200;
	bool active = false;
	PowerUpType type = Expand;

public:
	PowerUp(int x, int y);
	virtual ~PowerUp();
	virtual void start(SDL_Renderer* renderer) override;
	virtual void update(float deltaTime) override;
	virtual void render(SDL_Renderer* renderer) override;


	/**
	* Loads the textures for all PowerUp types.
	*/
	static void loadTextures(SDL_Renderer* renderer);
	/**
	* Destroys the textures for all PowerUp types.
	*/
	static void destroyTextures();
	bool isActive() const
	{
		return active;
	}
	void activate(PowerUpType type)
	{
		active = true;

		if (type >= 0 && type < 5)
			this->type = type;
	}
	void deactivate()
	{
		active = false;
	}
	PowerUpType getType() const
	{
		return type;
	}

};

