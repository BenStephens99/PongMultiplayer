#include "UIManager.h"
#include "TextureManager.h"

void UIComponent::drawUIComponent(SDL_Renderer* renderer)
{ 
	SDL_Rect position = { posX, posY, width, height };

	SDL_RenderCopy(renderer, texture, NULL, &position);
}


