#ifndef KHAIQUAT_H_INCLUDED
#define KHAIQUAT_H_INCLUDED
#include <iostream>
#include <vector>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "graphics.h"
#include "defs.h"
using namespace std;

const string numbers[13] = {"0","1","2","3","4","5","6","7","8","9","Skip","Reverse","+2"};
const string colors[4] = {"Red","Blue","Yellow","Green"};
const string specialCards[2] = {"Wild","Wild +4"};
bool direct = true;
int playerTurn = 100;
int cumlativeCards = 0;
struct card
{
    vector<string> number;
    vector<string> color;
};
int numberOfPlayers;

void drawCard(card &player)
{
    int wild = rand() % 10;
    if(wild != 3) {
        player.number.push_back(numbers[rand() % 13]);
        player.color.push_back(colors[rand() % 4]);
    }
    else {
        player.number.push_back(specialCards[rand() % 2]);
        player.color.push_back(specialCards[0]);
    }
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
SDL_Color whiteColor = {255, 255, 255, 255};
SDL_Color blackColor = {0, 0, 0, 255};

void chooseNumPlayer(Graphics graphics, TTF_Font* font)
{
    SDL_Texture* menu = graphics.loadTexture("numbersPlayersBG.jpg");
    graphics.prepareScene(menu);

    SDL_Texture* vs1 = graphics.loadTexture("1vs1white.png");
    graphics.DrawScaled(vs1, 280, 190, 200, 95);
    SDL_Texture* vs2 = graphics.loadTexture("1vs2white.png");
    graphics.DrawScaled(vs2, 300, 305, 188, 90);
    SDL_Texture* vs3 = graphics.loadTexture("1vs3white.png");
    graphics.DrawScaled(vs3, 300, 412, 180, 90);

    SDL_Texture* title = graphics.renderText("GAME  MODE", font, whiteColor);
    graphics.renderTexture(title, 250, 100);
    graphics.presentScene();

    SDL_Event event;
    int x, y;
    bool key[3] = {false};
    bool page2=true;
    while (page2) {
        SDL_GetMouseState(&x, &y);
        SDL_PollEvent(&event);
        if(x>307 && x<457 && y>192 && y<271) {
            if(!key[0]) {
                key[0]=true;
                SDL_DestroyTexture(vs1);
                vs1 = NULL;
                vs1 = graphics.loadTexture("1vs1green.png");
                graphics.DrawScaled(vs1, 300, 192, 176, 95);
                graphics.presentScene();
            }
                 }
        else if(key[0]) {
            key[0] = false;
            SDL_DestroyTexture(vs1);
            vs1 = NULL;
            vs1 = graphics.loadTexture("1vs1white.png");
            graphics.DrawScaled(vs1, 280, 190, 200, 95);
            graphics.presentScene();
        }
        if(x>307 && x<457 && y>302 && y<379) {
            if(!key[1]) {
                key[1]=true;
                SDL_DestroyTexture(vs2);
                vs2 = NULL;
                vs2 = graphics.loadTexture("1vs2green.png");
                graphics.DrawScaled(vs2, 301, 306, 179, 91);
                graphics.presentScene();
            }
                 }
        else if(key[1]) {
            key[1] = false;
            SDL_DestroyTexture(vs2);
            vs2 = NULL;
            vs2 = graphics.loadTexture("1vs2white.png");
            graphics.DrawScaled(vs2, 300, 305, 188, 90);
            graphics.presentScene();
        }
        if(x>307 && x<457 && y>408 && y<481) {
            if(!key[2]) {
                key[2]=true;
                SDL_DestroyTexture(vs3);
                vs3 = NULL;
                vs3 = graphics.loadTexture("1vs3green.png");
                graphics.DrawScaled(vs3, 304, 412, 177, 91);
                graphics.presentScene();
            }
                 }
        else if(key[2]) {
            key[2] = false;
            SDL_DestroyTexture(vs3);
            vs3 = NULL;
            vs3 = graphics.loadTexture("1vs3white.png");
            graphics.DrawScaled(vs3, 300, 412, 180, 90);
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
                 if(x>307 && x<457 && y>192 && y<271) {
                    numberOfPlayers = 2;
                    page2 = false;
                 }
                 else if(x>307 && x<457 && y>302 && y<379) {
                    numberOfPlayers = 3;
                    page2 = false;
                 }
                 else if(x>307 && x<457 && y>408 && y<481) {
                    numberOfPlayers = 4;
                    page2 = false;
                 }
                 break;
        }


    }
}

#endif // KHAIQUAT_H_INCLUDED
