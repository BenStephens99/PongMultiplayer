#pragma once
#include "MyGame.h"

class GameObject
{
public:

    int score;

    int posX;
    int posY;
    int height;
    int width;

    int speed;
    int velocity;

    SDL_Texture* texture;
    void drawGameObject(SDL_Renderer* renderer);
    void checkBounds();

    GameObject();

private:

};