#pragma once
#include "Entity.h"
#include "Text.h"

class Button : public Entity
{
	Text text;
	bool wasPressedInside = false;

public:
	Button(const std::string& buttonText, int x, int y, int w, int h);
	~Button();
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;
	bool isClicked();
};

