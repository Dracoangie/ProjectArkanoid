#pragma once
#include "Entity.h"
class Brick : public Entity
{
	int type = 1; // 1 for normal brick, 2 for strong brick, etc.
	int _type = 1;
	static  SDL_Texture* brickTextures[5]; // Static array to hold textures for different brick types
	static	SDL_Texture* brickDestroyedTexture; // Texture for destroyed brick
	bool destroyed = false;
	float destructionTimer = 0;
	int destructionFrame = 0;
public:
	bool active = true;

	Brick();
	Brick(int x, int y);
	Brick(int x, int y, int type);
	~Brick();

	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	int getType() const { return _type; }
	void setType(int newType){ type = newType; _type = newType; }

	bool destroyBrick();
	bool isDestroyed() const { return destroyed; }

	/**
	* Loads the textures for all brick types.
	*/
	static void loadTextures(SDL_Renderer* renderer);
	/**
	* Destroys the textures for all brick types. 
	*/
	static void destroyTextures();
};

