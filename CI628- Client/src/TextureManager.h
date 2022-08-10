#pragma once
#include "MyGame.h"

class Texture {


public:
    static SDL_Texture* LoadImageTexture(const char* file, SDL_Renderer* renderer);
    static SDL_Texture* LoadTextTexture(const char* text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color color);
};