#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"

#include "TextureManager.h"
#include "GameObject.h"
#include "UIManager.h"
#include "Player.h"


static struct GameData {
    int player1Y = 0;
    int player2Y = 0;
    int ballX = 0;
    int ballY = 0;
} game_data;

static struct PreGameData {
    bool player1joined = false;
    int player2joined = false;
    int player1ready = false;
    int player2ready = false;
} pre_game_data;

class MyGame {

private:


public:
    std::vector<std::string> messages;

    void init(SDL_Renderer* renderer);
    void initPreGameUI(SDL_Renderer* renderer);
    void initGameObjects(SDL_Renderer* renderer);
    void initInGameUI(SDL_Renderer* renderer);
    void initSounds();
    void on_receive(std::string message, std::vector<std::string>& args);
    void start();
    void playerJoined(int p);
    void send(std::string message);
    void input(SDL_Event& event);
    void movePlayer(int player);
    void update();
    void render(SDL_Renderer* renderer);
    void waitingScreen(SDL_Renderer* renderer);
    void DestroyWaitingRoomUI();
    void updateScores(SDL_Renderer* renderer);
   // int renderParticals(SDL_Renderer* renderer);
   
};

#endif
