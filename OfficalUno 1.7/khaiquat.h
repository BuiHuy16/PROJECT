#ifndef KHAIQUAT_H_INCLUDED
#define KHAIQUAT_H_INCLUDED
#include <iostream>
#include <windows.h>
#include <vector>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "graphics.h"

const string numbers[13] = {"0","1","2","3","4","5","6","7","8","9","skip","reverse","draw2"};
const string colors[4] = {"red","blue","yellow","green"};
const string specialCards[3] = {"wild","change","draw4"};
bool direct = true;
int playerTurn = 12;
int cumlativeCards = 0;

struct card
{
    string number;
    string color;
};
struct Mouse {
    double x, y;
    SDL_Texture* texture;
    double dx = 0, dy = 0;
    void move() {
        x += dx;
        y += dy;
    }
    void turnNorth(float speed) {
        dy = -speed;
    }
    void turnSouth(float speed) {
        dy = speed;
    }
    void turnWest(float speed) {
        dx = -speed;
    }
    void turnEast(float speed) {
        dx = speed;
    }
};
struct Vector {
    double x,y;
    Vector(double _x, double _y) {
        x = _x;
        y = _y;
    }
};
int numberOfPlayers;
card pile;


vector<card> player1, player2, player3, player4;

SDL_Color whiteColor = {255, 255, 255, 255};
SDL_Color blackColor = {0, 0, 0, 255};
SDL_Color blueColor = {100, 100, 255, 255};
SDL_Color greenColor = {0, 255, 0, 255};
SDL_Color redColor = {255, 0, 0, 255};
SDL_Color yellowColor = {255, 255, 0, 255};

vector<Mouse> myCard;

void drawCard(vector<card> &player)
{
    int wild = rand() % 10;
    if(wild != 3) {
        player.push_back({numbers[rand() % 13], colors[rand() % 4] });
    }
    else {
        player.push_back({specialCards[rand() % 2 + 1], specialCards[0] });
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

SDL_Texture* menu1 = loadTexture("menuBG.jpg");
SDL_Texture* playText;
SDL_Texture* quitText;
SDL_Texture* menu2 = loadTexture("numbersPlayersBG.jpg");
SDL_Texture* vs1white = loadTexture("1vs1white.png");
SDL_Texture* vs1green = loadTexture("1vs1green.png");
SDL_Texture* vs2white = loadTexture("1vs2white.png");
SDL_Texture* vs2green = loadTexture("1vs2green.png");
SDL_Texture* vs3white = loadTexture("1vs3white.png");
SDL_Texture* vs3green = loadTexture("1vs3green.png");

SDL_Texture* avatar = loadTexture("unknown.jfif");
SDL_Texture* whiteFrame = loadTexture("nentrang.png");
SDL_Texture* secretCards = loadTexture("Cards/secretcard.png");
SDL_Texture* endGame = loadTexture("endscreen.jpg");
#endif // KHAIQUAT_H_INCLUDED
