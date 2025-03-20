#ifndef LOOPGAME_H_INCLUDED
#define LOOPGAME_H_INCLUDED

#include "khaiquat.h"
#include "game.h"
void chooseNumPlayer(Graphics graphics, TTF_Font* font)
{
    SDL_Texture* menu = graphics.loadTexture("numbersPlayersBG.jpg");
    graphics.prepareScene(menu);

    SDL_Texture* vs1 = graphics.loadTexture("1vs1white.png");
    graphics.DrawScaled(vs1, 480, 190, 200, 95);
    SDL_Texture* vs2 = graphics.loadTexture("1vs2white.png");
    graphics.DrawScaled(vs2, 500, 305, 188, 90);
    SDL_Texture* vs3 = graphics.loadTexture("1vs3white.png");
    graphics.DrawScaled(vs3, 500, 412, 180, 90);

    SDL_Texture* title = graphics.renderText("GAME  MODE", font, whiteColor);
    graphics.renderTexture(title, 450, 100);
    graphics.presentScene();

    SDL_Event event;
    int x, y;
    bool key[3] = {false};
    bool page2=true;
    while (page2) {
        SDL_GetMouseState(&x, &y);
        SDL_PollEvent(&event);
        if(x>507 && x<657 && y>192 && y<271) {
            if(!key[0]) {
                key[0]=true;
                SDL_DestroyTexture(vs1);
                vs1 = NULL;
                vs1 = graphics.loadTexture("1vs1green.png");
                graphics.DrawScaled(vs1, 500, 192, 176, 95);
                graphics.presentScene();
            }
                 }
        else if(key[0]) {
            key[0] = false;
            SDL_DestroyTexture(vs1);
            vs1 = NULL;
            vs1 = graphics.loadTexture("1vs1white.png");
            graphics.DrawScaled(vs1, 480, 190, 200, 95);
            graphics.presentScene();
        }
        if(x>507 && x<657 && y>302 && y<379) {
            if(!key[1]) {
                key[1]=true;
                SDL_DestroyTexture(vs2);
                vs2 = NULL;
                vs2 = graphics.loadTexture("1vs2green.png");
                graphics.DrawScaled(vs2, 501, 306, 179, 91);
                graphics.presentScene();
            }
                 }
        else if(key[1]) {
            key[1] = false;
            SDL_DestroyTexture(vs2);
            vs2 = NULL;
            vs2 = graphics.loadTexture("1vs2white.png");
            graphics.DrawScaled(vs2, 500, 305, 188, 90);
            graphics.presentScene();
        }
        if(x>507 && x<657 && y>408 && y<481) {
            if(!key[2]) {
                key[2]=true;
                SDL_DestroyTexture(vs3);
                vs3 = NULL;
                vs3 = graphics.loadTexture("1vs3green.png");
                graphics.DrawScaled(vs3, 504, 412, 177, 91);
                graphics.presentScene();
            }
                 }
        else if(key[2]) {
            key[2] = false;
            SDL_DestroyTexture(vs3);
            vs3 = NULL;
            vs3 = graphics.loadTexture("1vs3white.png");
            graphics.DrawScaled(vs3, 500, 412, 180, 90);
            graphics.presentScene();
        }
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONDOWN:
                 cerr << "Down at (" << x << ", " << y << ")\n";
                 break;
            case SDL_MOUSEBUTTONUP:
                 cerr << "Up at (" << x << ", " << y << ")\n";
                 if(x>507 && x<657 && y>192 && y<271) {
                    numberOfPlayers = 2;
                    page2 = false;
                 }
                 else if(x>507 && x<657 && y>302 && y<379) {
                    numberOfPlayers = 3;
                    page2 = false;
                 }
                 else if(x>507 && x<657 && y>408 && y<481) {
                    numberOfPlayers = 4;
                    page2 = false;
                 }
                 break;
        }


    }
}
void startGame(Graphics graphics)
{
    while(player1.number.size() !=0 && player2.number.size() !=0 && player3.number.size() !=0 && player4.number.size() !=0) { //gameloop
        switch (abs(playerTurn) % numberOfPlayers + 1) {
            case 1:
                rendergame(graphics);
                //playerDanhBai(player1, pile, numberOfPlayers);
                break;
            case 2:
                rendergame(graphics);
                //ai(player2, pile, numberOfPlayers);
                break;
            case 3:
                rendergame(graphics);
                //ai(player3, pile, numberOfPlayers);
                break;
            case 4:
                rendergame(graphics);
                //ai(player4, pile, numberOfPlayers);
                break;
        }
    }
}

#endif // LOOPGAME_H_INCLUDED
