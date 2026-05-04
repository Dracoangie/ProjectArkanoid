#include "Text.h"

TTF_Font* Text::fonts[(int)FontType::count] = { nullptr };

Text::Text()
{
	transform.x = 0;
	transform.y = 0;
	transform.w = 100;
	transform.h = 100;
	texture = nullptr;
	textSurface = nullptr;
}

Text::Text(const std::string& text, float x, float y, float scale)
{
	this->text = text;
	this->scale = scale;
	transform.x = x;
	transform.y = y;
	transform.w = 100;
	transform.h = 100;
	texture = nullptr;
	textSurface = nullptr;
}

Text::Text(Text&& other) noexcept
{
	transform = other.transform;
	texture = other.texture;
	fontType = other.fontType;
	color = other.color;
	text = std::move(other.text);
	textSurface = other.textSurface;
	scale = other.scale;

	other.texture = nullptr;
	other.textSurface = nullptr;
}

Text& Text::operator=(Text&& other) noexcept
{
	if (this != &other)
	{
		if (texture)
			SDL_DestroyTexture(texture);

		if (textSurface)
			SDL_FreeSurface(textSurface);

		transform = other.transform;
		texture = other.texture;
		fontType = other.fontType;
		color = other.color;
		text = std::move(other.text);
		textSurface = other.textSurface;
		scale = other.scale;

		other.texture = nullptr;
		other.textSurface = nullptr;
	}

	return *this;
}

Text::~Text()
{
	if (textSurface)
	{
		SDL_FreeSurface(textSurface);
		textSurface = nullptr;
	}
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
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	if (textSurface)
	{
		SDL_FreeSurface(textSurface);
		textSurface = nullptr;
	}

	TTF_Font* font = fonts[(int)fontType];

	if (!font)
		return;

	textSurface = TTF_RenderText_Blended(font, text.c_str(), color);

	if (!textSurface)
		return;

	transform.w = textSurface->w * scale;
	transform.h = textSurface->h * scale;
}

void Text::setFont(FontType type)
{
	fontType = type;
	setText(text);
}

void Text::setColor(const SDL_Color& newColor)
{
	color = newColor;
	setText(text);
}

bool Text::loadFonts()
{
	fonts[(int)FontType::Default] = TTF_OpenFont("assets/fonts/DePixelHalbfett.ttf", 24);
	fonts[(int)FontType::Title] = TTF_OpenFont("assets/fonts/04B30.ttf", 24);

	if (!fonts[(int)FontType::Default])
		return false;

	if (!fonts[(int)FontType::Title])
		return false;

	return true;
}

void Text::destroyFonts()
{
	for (int i = 0; i < (int)FontType::count; i++)
	{
		if (fonts[i])
		{
			TTF_CloseFont(fonts[i]);
			fonts[i] = nullptr;
		}
	}
}