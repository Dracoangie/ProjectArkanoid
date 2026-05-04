#pragma once
#include "Entity.h"

enum class FontType
{
	Default,
	Title,
	count
};

class Text : public Entity
{
	static TTF_Font* fonts[(int)FontType::count];

	FontType fontType = FontType::Default;
	SDL_Color color = { 255, 255, 255, 255 };
	std::string text;
	SDL_Surface* textSurface = nullptr;
	float scale = 1;

public:
	Text();
	Text(const std::string& text, float x, float y, float scale = 1.0f);
	static bool loadFonts();
	static void destroyFonts();

	void start(SDL_Renderer* renderer) override;
	void update(float deltaTime) override;
	void render(SDL_Renderer* renderer) override;

	Text(const Text&) = delete;
	Text& operator=(const Text&) = delete;

	Text(Text&& other) noexcept;
	Text& operator=(Text&& other) noexcept;

	void setFont(FontType type);
	void setText(const std::string& newText);
	void setColor(const SDL_Color& newColor);

	~Text();
};

