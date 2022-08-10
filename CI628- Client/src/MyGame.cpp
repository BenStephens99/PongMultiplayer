#include "MyGame.h"
#include <random>
#include <SDL_timer.h>
#include "../build/Player.h"

bool inPreGame = true;
bool gameRunning = false;

int assignedPlayer = 0;
int paddleSpeed = 8.5;

int timer;

TTF_Font* BRLNSR;

Player player1;
Player player2;
GameObject ball;

GameObject partical1;
GameObject partical2;
GameObject partical3;

Mix_Music* wallEffect;
Mix_Music* batEffect;
Mix_Music* goalEffect;

UIComponent pongLogo;

UIComponent background;
UIComponent player1ScoreUI;
UIComponent player2ScoreUI;
UIComponent scoreboard;

UIComponent player1UI;
UIComponent player2UI;

UIComponent player1JoinedUI;
UIComponent player2JoinedUI;

UIComponent player1ReadyUI;
UIComponent player2ReadyUI;

UIComponent preGameTimerUI;

UIComponent pressRUI;
UIComponent youUI;

SDL_Color White = { 255, 255, 255, 255 };
SDL_Color Blue = { 0, 100, 255, 255};
SDL_Color Red = { 255, 40, 0, 200 };
SDL_Color Green = { 0, 214, 7, 255 };

void MyGame::initPreGameUI(SDL_Renderer* renderer) {

    pongLogo.texture = Texture::LoadImageTexture("images/pongLogo.bmp", renderer);
    pongLogo.height = 100;
    pongLogo.width = 257;
    pongLogo.posY = 20;
    pongLogo.posX = (800 / 2) - (pongLogo.width / 2);

    player1UI.texture = Texture::LoadTextTexture("PLAYER 1", BRLNSR, renderer, Blue);
    player2UI.texture = Texture::LoadTextTexture("PLAYER 2", BRLNSR, renderer, Red);
  
    player1JoinedUI.texture = Texture::LoadTextTexture("Joined", BRLNSR, renderer, White);
    player2JoinedUI.texture = Texture::LoadTextTexture("Joined", BRLNSR, renderer, White);

    player1ReadyUI.texture = Texture::LoadTextTexture("READY", BRLNSR, renderer, Green);
    player2ReadyUI.texture = Texture::LoadTextTexture("READY", BRLNSR, renderer, Green);

    int playerUIHeight = 30;
    int playerUIWidth = 100;
    int playerUIY = (600/2) - 100; 
    int playerUIX = (800 / 2) - (playerUIWidth / 2) - 200;

    player1UI.height = playerUIHeight;
    player1UI.width = playerUIWidth;
    player1UI.posY = playerUIY;
    player1UI.posX = playerUIX;

    player2UI.height = playerUIHeight;
    player2UI.width = playerUIWidth;
    player2UI.posY = playerUIY + (playerUIHeight + 15);
    player2UI.posX = playerUIX;

    youUI.texture = Texture::LoadTextTexture("(You)", BRLNSR, renderer, White);
    youUI.width = 50;
    youUI.height = playerUIHeight;
    switch (assignedPlayer) {
    case 1:
        youUI.posX = player1UI.posX + playerUIWidth + 10;
        youUI.posY = player1UI.posY;
        break;
    case 2:
        youUI.posX = player2UI.posX + playerUIWidth + 10;
        youUI.posY = player2UI.posY;
        break;
    }

    player1JoinedUI.height = playerUIHeight;
    player1JoinedUI.width = playerUIWidth;
    player1JoinedUI.posY = playerUIY; 
    player1JoinedUI.posX = youUI.posX + youUI.width + 150;

    player1ReadyUI.height = playerUIHeight;
    player1ReadyUI.width = playerUIWidth;
    player1ReadyUI.posY = playerUIY;
    player1ReadyUI.posX = player1JoinedUI.posX + player1UI.width + 30;

    player2JoinedUI.height = playerUIHeight;
    player2JoinedUI.width = playerUIWidth;
    player2JoinedUI.posY = player2UI.posY; 
    player2JoinedUI.posX = youUI.posX + youUI.width + 150;

    player2ReadyUI.height = playerUIHeight;
    player2ReadyUI.width = playerUIWidth;
    player2ReadyUI.posY = player2UI.posY; 
    player2ReadyUI.posX = player2JoinedUI.posX + player2UI.width + 30;

    pressRUI.texture = Texture::LoadTextTexture("PRESS 'R' TO READY UP!", BRLNSR, renderer, White);
    pressRUI.width = 450;
    pressRUI.height = 70;   
    pressRUI.posX = (800/2) - (pressRUI.width / 2);
    pressRUI.posY = 450;


    preGameTimerUI.texture = Texture::LoadTextTexture("0", BRLNSR, renderer, Blue);
    preGameTimerUI.height = 100;
    preGameTimerUI.width = 100;
    preGameTimerUI.posY = 200;
    preGameTimerUI.posX = (800 / 2) - (preGameTimerUI.width / 2);

}

void MyGame::initGameObjects(SDL_Renderer* renderer) {
    
    player1.texture = Texture::LoadImageTexture("images/paddle.bmp", renderer);
    player1.posX = 200;
    player1.posY = 300;
    player1.width = 55;
    player1.height = 80;

    player2.texture = Texture::LoadImageTexture("images/paddle2.bmp", renderer);
    player2.posX = 570;
    player2.posY = 300;
    player2.width = 55;
    player2.height = 80;

    ball.texture = Texture::LoadImageTexture("images/ball.bmp", renderer);
    ball.posX = 200;
    ball.posY = 100;
    ball.width = 20;
    ball.height = 20;

    partical1.texture = Texture::LoadImageTexture("images/ball.bmp", renderer);
    partical1.width = 5;
    partical1.height = 5;   
    
    partical2.texture = Texture::LoadImageTexture("images/ball.bmp", renderer);
    partical2.width = 5;
    partical2.height = 5;   
    
    partical3.texture = Texture::LoadImageTexture("images/ball.bmp", renderer);
    partical3.width = 5;
    partical3.height = 5;
   
}
void MyGame::initInGameUI(SDL_Renderer* renderer) {

    int scoreWidths = 50;
    int scoreHeights = 70;

    player1ScoreUI.texture = Texture::LoadTextTexture("0", BRLNSR, renderer, White);
    player1ScoreUI.posX = 235;
    player1ScoreUI.posY = 10;
    player1ScoreUI.width = scoreWidths;
    player1ScoreUI.height = scoreHeights;

    player2ScoreUI.texture = Texture::LoadTextTexture("0", BRLNSR, renderer, White);
    player2ScoreUI.posX = 515;
    player2ScoreUI.posY = 10;
    player2ScoreUI.width = scoreWidths;
    player2ScoreUI.height = scoreHeights;

    scoreboard.texture = Texture::LoadImageTexture("images/scoreboard.bmp", renderer);
    scoreboard.posY = 0;
    scoreboard.height = 93;
    scoreboard.width = 365;
    scoreboard.posX = (800/2) - (scoreboard.width/2);

    background.texture = Texture::LoadImageTexture("images/background.bmp", renderer);
    background.posX = 0;
    background.posX = 0;
    background.width = 800;
    background.height = 600;

}
void MyGame::initSounds() {
    
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);

    wallEffect = Mix_LoadMUS("sounds/bounce.mp3");
    batEffect = Mix_LoadMUS("sounds/bounce.mp3");
    goalEffect = Mix_LoadMUS("sounds/explode.mp3");
}

void MyGame::init(SDL_Renderer* renderer) {

    BRLNSR = TTF_OpenFont("fonts/BRLNSR.ttf", 192);
    
    MyGame::initPreGameUI(renderer);

    MyGame::initGameObjects(renderer);

    MyGame::initInGameUI(renderer);

    MyGame::initSounds();

  
}

bool to_bool(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    std::istringstream is(str);
    bool b;
    is >> std::boolalpha >> b;
    return b;
}

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {

    if (cmd == "PRE GAME TIMER: ") {
        timer = stoi(args.at(0)) + 1;
    }

    if (cmd == "start") {
        MyGame::start();
        
    } else if (cmd == "stop") {
        gameRunning = false;
    }

    if (cmd == "GAME_DATA")
    {
        // we should have exactly 4 arguments
        if (args.size() == 4)
        {
            game_data.player1Y = stoi(args.at(0));
            game_data.player2Y = stoi(args.at(1));
            game_data.ballX = stoi(args.at(2));
            game_data.ballY = stoi(args.at(3));
        }
    } else if (cmd == "PRE_GAME") {
        // we should have exactly 4 arguments
        if (args.size() == 4)
        {
            pre_game_data.player1joined = to_bool(args.at(0));
            pre_game_data.player2joined = to_bool(args.at(1));
            pre_game_data.player1ready = to_bool(args.at(2));
            pre_game_data.player2ready = to_bool(args.at(3));
        }
    }
        
    else {
        std::cout << "Received: " << cmd << std::endl;
    };

    if (cmd == "PLAYER_1") {
        //checks player hasnt already been assigned a player
        if (assignedPlayer == 0) {
            send("Player 1 joining");
            assignedPlayer = 1;
        }
    } else if (cmd == "PLAYER_2") {
        if (assignedPlayer == 0)
        {
            assignedPlayer = 2;
            send("Player 2 joining");
        }
    }

    if (cmd == "SCORES")
    {
        if (args.size() == 2)
        {
            player1.score = std::stoi(args.at(0));

            player2.score = std::stoi(args.at(1));

            Mix_PlayMusic(goalEffect, 0);
        }
     
    }

    //if message starts with .. play effect
    if (cmd.rfind("BALL_HIT_BAT", 0) == 0) { 

        Mix_PlayMusic(batEffect, 1);

    } else if (cmd.rfind("HIT_WALL_UP", 0) == 0) {

        Mix_PlayMusic(batEffect, 1);

    } else if (cmd.rfind("HIT_WALL_DOWN", 0) == 0) {

        Mix_PlayMusic(batEffect, 1);

    }

}

void MyGame::start() {
    inPreGame = false;
    gameRunning = true;
    MyGame::DestroyWaitingRoomUI();
    preGameTimerUI.posY = -5;
}

void MyGame::send(std::string message) {

    messages.push_back(message);

}

void MyGame::input(SDL_Event& event) {

    switch (event.key.keysym.sym) {

    case SDLK_w:
        
        switch (assignedPlayer) 
        {
    
        case 1: //player 1 up
              send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");

              if (event.type == SDL_KEYDOWN) 
              {
                player1.velocity = paddleSpeed;
              }
              else 
              {
                player1.velocity = 0;
              }
              break;
           
        case 2: //player 2 up
             send(event.type == SDL_KEYDOWN ? "I_DOWN" : "I_UP");

             if (event.type == SDL_KEYDOWN) 
             {
                player2.velocity = -paddleSpeed;
             }
             else 
             {
               player2.velocity = 0;
             }
             break;

        }
    break;

    case SDLK_s:
        
        switch (assignedPlayer)
        {
        case 1: // player 1 down
            send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");

            if (event.type == SDL_KEYDOWN) 
            {
                player1.velocity = paddleSpeed;
            }
            else 
            {
                player1.velocity = 0;
            }
            break;

        case 2:  //player 2 down
            send(event.type == SDL_KEYDOWN ? "K_DOWN" : "K_UP");

            if (event.type == SDL_KEYDOWN)
            {
                player2.velocity = paddleSpeed;
            }
            else
            {
                player2.velocity = 0;
            }
            break;
        }

    break;

    case SDLK_r:

        switch (assignedPlayer) {
        case 1:
            player1.ready = true;
            send("player" + std::to_string(assignedPlayer) + "Ready");
            break;
        case 2:
            player2.ready = true;
            send("player" + std::to_string(assignedPlayer) + "Ready");
            break;
        }
    }
}

void MyGame::movePlayer(int player) {
    switch (player) {

    case 1:
        //moves player based on input
        player1.posY += player1.velocity;

        player1.checkBounds();

        //moves other player based on server message
        player2.posY = game_data.player2Y;

        //checks if player is within 20 pixles of server position and if not snaps them back
        if (player1.posY >= game_data.player1Y + 20 || player1.posY <= game_data.player1Y + 20) {

            player1.posY = game_data.player1Y;
        }
        break;

    case 2:
        player2.posY += player2.velocity;

        player2.checkBounds();

        player1.posY = game_data.player1Y;

        if (player2.posY >= game_data.player2Y + 20 || player2.posY <= game_data.player2Y + 20) {

            player2.posY = game_data.player2Y;
        }
        break;
    }
}

void MyGame::update() {

    if (gameRunning) {
    
        MyGame::movePlayer(assignedPlayer);
    
        ball.posY = game_data.ballY;
        ball.posX = game_data.ballX;
    }
    else if (inPreGame) {
        player1.joined = pre_game_data.player1joined;
        player2.joined = pre_game_data.player2joined;
        player1.ready = pre_game_data.player1ready;
        player2.ready = pre_game_data.player2ready;
    }
  
}

void MyGame::render(SDL_Renderer* renderer) {
    
 

   if (gameRunning) 
   {
        background.drawUIComponent(renderer);

        scoreboard.drawUIComponent(renderer);
        
        player1.drawGameObject(renderer);
        
        player2.drawGameObject(renderer);
        
        ball.drawGameObject(renderer);

        MyGame::updateScores(renderer);
   }
   else if (inPreGame) {
       waitingScreen(renderer);
   }

   if (timer > 0) {

       std::stringstream ss;
       ss << timer;
       std::string str1 = ss.str();

       const char* timerChar = str1.c_str();

       preGameTimerUI.drawUIComponent(renderer);
       SDL_DestroyTexture(preGameTimerUI.texture);
       preGameTimerUI.texture = Texture::LoadTextTexture(timerChar, BRLNSR, renderer, White);
   }

}

void MyGame::waitingScreen(SDL_Renderer* renderer) {


    pongLogo.drawUIComponent(renderer);

    player1UI.drawUIComponent(renderer);
    player2UI.drawUIComponent(renderer);

    pressRUI.drawUIComponent(renderer);
    youUI.drawUIComponent(renderer);
    
    if (player1.joined) {
        player1JoinedUI.drawUIComponent(renderer);
    } 
    
    if (player2.joined) {
        player2JoinedUI.drawUIComponent(renderer);
    }

    if (player1.ready) {
        player1ReadyUI.drawUIComponent(renderer);
    }

    if (player2.ready) {
        player2ReadyUI.drawUIComponent(renderer);
    }
   
    

}

void MyGame::DestroyWaitingRoomUI() {
    
    SDL_DestroyTexture(player1ReadyUI.texture);
    SDL_DestroyTexture(player1UI.texture);
    SDL_DestroyTexture(player2UI.texture);
    SDL_DestroyTexture(player2ReadyUI.texture);
    SDL_DestroyTexture(pressRUI.texture);
    SDL_DestroyTexture(youUI.texture);
    SDL_DestroyTexture(player1JoinedUI.texture);
    SDL_DestroyTexture(player2JoinedUI.texture);
}

void MyGame::updateScores(SDL_Renderer* renderer) {
    
    std::stringstream ss;
    ss << player1.score;
    std::string str1 = ss.str();

    std::stringstream ss2;
    ss2 << player2.score;
    std::string str2 = ss2.str();

    const char* p1Score = str1.c_str();
    const char* p2Score = str2.c_str();

    player1ScoreUI.drawUIComponent(renderer);
    SDL_DestroyTexture(player1ScoreUI.texture);
    player1ScoreUI.texture = Texture::LoadTextTexture(p1Score, BRLNSR, renderer, White);

    player2ScoreUI.drawUIComponent(renderer);
    SDL_DestroyTexture(player2ScoreUI.texture);
    player2ScoreUI.texture = Texture::LoadTextTexture(p2Score, BRLNSR, renderer, White);
}
