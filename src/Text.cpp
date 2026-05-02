#include "Text.h"

Text::Text()
{
	transform.x = 0;
	transform.y = 0;
	transform.w = 100;
	transform.h = 100;
	font = TTF_OpenFont("assets/fonts/DePixelHalbfett.ttf", 24);
	color = {255, 255, 255, 255};
	texture = nullptr;
	textSurface = nullptr;
}

Text::Text(const std::string& initialText) : Text()
{
	transform.h = 100;
	transform.w = 15 * initialText.length();
	setText(initialText);
}

Text::Text(const std::string& initialText, int scale) : Text(initialText)
{
	transform.w = initialText.length() * scale;
	transform.h = 2.5f * scale;
}

Text::Text(const std::string& initialText, int x, int y, int scale) : Text(initialText, scale)
{
	transform.x = x;
	transform.y = y;
}

Text::Text(const std::string& initialText, int x, int y, int w, int h) : Text(initialText)
{
	transform.x = x;
	transform.y = y;
	transform.w = w;
	transform.h = h;
}

Text::~Text()
{
	if (texture)
		SDL_DestroyTexture(texture);
}

void Text::start(SDL_Renderer* renderer)
{
}

void Text::update(float deltaTime)
{
}

void Text::render(SDL_Renderer* renderer)
{
	if(textSurface)
	{
		if (texture)
			SDL_DestroyTexture(texture);
		texture = SDL_CreateTextureFromSurface(renderer, textSurface);
		SDL_FreeSurface(textSurface);
		textSurface = nullptr;
	}
	if (!texture)
		return;
	SDL_Rect dstRect = {
		(int)transform.x,
		(int)transform.y,
		transform.w,
		transform.h
	};
	SDL_RenderCopy(renderer, texture, NULL, &dstRect);
}

void Text::setText(const std::string& newText)
{
	text = newText;
	if (texture)
		SDL_DestroyTexture(texture);
	textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
}

void Text::setFont(TTF_Font* newFont)
{
	font = newFont;
	setText(text);
}

void Text::setColor(const SDL_Color& newColor)
{
	color = newColor;
	setText(text);
}