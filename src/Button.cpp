#include "Button.h"

Button::Button(const std::string& buttonText, int x, int y, int w, int h)
{
	transform.x = x;
	transform.y = y;
	transform.w = w;
	transform.h = h;
	text = Text(buttonText, x + 10, y + 10, 1);
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
}

void Button::render(SDL_Renderer* renderer)
{
	SDL_Rect transformRect = {
		(int)transform.x,
		(int)transform.y,
		transform.w,
		transform.h
	};
	SDL_SetRenderDrawColor(renderer, 70, 75, 90, 255);
	SDL_RenderFillRect(renderer, &transformRect);
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