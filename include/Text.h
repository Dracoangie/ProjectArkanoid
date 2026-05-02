#pragma once
#include "Entity.h"

class Text : public Entity
{
	TTF_Font* font;
	SDL_Color color;
	std::string text;
	SDL_Surface* textSurface;

public:
	Text();
	Text(const std::string& initialText);
	Text(const std::string& initialText, int scale);
	Text(const std::string& initialText, int x, int y, int scale);
	Text(const std::string& initialText, int x, int y, int w, int h);
	~Text();
	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	void setText(const std::string& newText);
	void setFont(TTF_Font* newFont);
	void setColor(const SDL_Color& newColor);
};

