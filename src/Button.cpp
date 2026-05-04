#include "Button.h"

Button::Button(const std::string& buttonText, float x, float y, float scale) : text(buttonText, x + 10, y + 10, scale)
{
	transform.x = x;
	transform.y = y;
	text.setFont(FontType::Title);
	transform.w = text.transform.w + 20;
	transform.h = text.transform.h + 20;
}

Button::~Button()
{
}

void Button::start(SDL_Renderer* renderer)
{
	text.start(renderer);
}

void Button::update(float deltaTime)
{

	text.update(deltaTime);
	int mouseX, mouseY = 0;
	Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	if(mouseX >= transform.x && mouseX <= transform.x + transform.w &&
		mouseY >= transform.y && mouseY <= transform.y + transform.h)
		text.setColor(onHoverColor);
	else
		text.setColor(backgroundColor);
}

void Button::render(SDL_Renderer* renderer)
{
	text.render(renderer);
}

bool Button::isClicked()
{
	int mouseX, mouseY = 0;
	Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseState && SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		return mouseX >= transform.x && mouseX <= transform.x + transform.w &&
			mouseY >= transform.y && mouseY <= transform.y + transform.h;
	}
	return false;
}