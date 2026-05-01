#pragma once


#include "Utils.h"

class Entity
{
protected:
	/**
	 * The texture of the entity, used for rendering. 
	 * It is loaded in the start() method and destroyed in the destructor of the derived class.
	 */
	SDL_Texture* texture = nullptr;

public:
	/**
	 * The transform component of the entity, containing its position and size.
	 */
	Transform transform{0,0,0,0};

	virtual ~Entity()
	{
		if(texture)
			SDL_DestroyTexture(texture);
	}

	/**
	 * Is called once when the entity is added to the scene. 
	 * It is used to load the texture and initialize any other resources needed by the entity.
	 */
	virtual void start(SDL_Renderer* renderer) = 0;

	/**
	 * Is called every frame to update the entity's state.
	 */
	virtual void update(float deltaTime) = 0;

	/**
	 * Is called every frame to render the entity on the screen.
	 */
	virtual void render(SDL_Renderer* renderer) = 0;

};

