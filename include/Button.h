#pragma once
#include "Entity.h"
#include "Text.h"

class Button : public Entity
{
	Text text;
	SDL_Color backgroundColor = { 245, 255, 232, 255 };
	SDL_Color onHoverColor = { 146, 232, 192, 255 };

public:
	Button(const std::string& buttonText, float x, float y, float scale);
	~Button();
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void setTextPosition(float x, float y)
	{
		text.transform.x = x + 10;
		text.transform.y = y + 10;
		transform.x = x;
		transform.y = y;
		transform.w = text.transform.w + 20;
		transform.h = text.transform.h + 20;

	}
	bool isClicked();
};

