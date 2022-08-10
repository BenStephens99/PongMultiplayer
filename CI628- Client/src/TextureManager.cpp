#include "TextureManager.h"

SDL_Texture* Texture::LoadImageTexture(const char* file, SDL_Renderer* renderer) {

    SDL_Surface* surface = SDL_LoadBMP(file);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return(texture);
}

SDL_Texture* Texture::LoadTextTexture(const char* text, TTF_Font* font, SDL_Renderer* renderer, SDL_Color color) {

    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    return(texture);
}

