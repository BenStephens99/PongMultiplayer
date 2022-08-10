#include "GameObject.h"

GameObject::GameObject(){

    posX = 0;
    posY = 0;
    width = 0;
    height = 0;
    texture = nullptr;
    speed = 0;
    velocity = 0;
    score = 0;
}

void GameObject::drawGameObject(SDL_Renderer* renderer)
{
    SDL_Rect destination = { posX, posY, width, height };
    SDL_RenderCopy(renderer, texture, NULL, &destination);
}

void GameObject::checkBounds() {
    if (posY >= 600 - height) {
        posY = 600 - height;
    }
    else if (posY <= 0) {
        posY = 0;
    }
}