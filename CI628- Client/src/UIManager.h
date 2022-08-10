#pragma once
#include "MyGame.h"

class UIComponent 
{
public:
	
	int posX;
	int posY;
	int width;
	int height;

	SDL_Texture* texture;
	void drawUIComponent(SDL_Renderer* renderer);
};

