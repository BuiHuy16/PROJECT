#ifndef KHAIQUAT_H_INCLUDED
#define KHAIQUAT_H_INCLUDED
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "graphics.h"

const string numbers[13] = {"1","2","3","4","5","6","7","8","9","0","draw2","skip","reverse"};
const string colors[4] = {"yellow","red","blue","green"};
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
vector<string> namePlayer;

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

SDL_Texture* menu1 = loadTexture("assests/images/menuBG.jpg");
SDL_Texture* playText;
SDL_Texture* quitText;
SDL_Texture* play2;
SDL_Texture* keepText;

SDL_Texture* menu2 = loadTexture("assests/images/numbersPlayersBG.jpg");
SDL_Texture* vs1white = loadTexture("assests/images/1vs1white.png");
SDL_Texture* vs1green = loadTexture("assests/images/1vs1green.png");
SDL_Texture* vs2white = loadTexture("assests/images/1vs2white.png");
SDL_Texture* vs2green = loadTexture("assests/images/1vs2green.png");
SDL_Texture* vs3white = loadTexture("assests/images/1vs3white.png");
SDL_Texture* vs3green = loadTexture("assests/images/1vs3green.png");
SDL_Texture* tickImg = loadTexture("assests/images/tickkk.png");
SDL_Texture* avatar = loadTexture("assests/images/unknown.jfif");
SDL_Texture* emptySquare = loadTexture("assests/images/nentrang.png");
SDL_Texture* whiteFrame = loadTexture("assests/images/nentrang.png");
SDL_Texture* secretCards = loadTexture("assests/images/cards.png");
SDL_Texture* endGame = loadTexture("assests/images/endscreen.jpg");
SDL_Texture* mui1 = loadTexture("assests/images/mui1.png");
SDL_Texture* mui2 = loadTexture("assests/images/mui2.png");
SDL_Texture* mui3 = loadTexture("assests/images/mui3.png");
SDL_Texture* mui4 = loadTexture("assests/images/mui4.png");
SDL_Texture* nope = loadTexture("assests/images/nope.png");
SDL_Texture* arrow = loadTexture("assests/images/down.png");
SDL_Texture* secretCard = loadTexture("assests/images/secret.png");
SDL_Texture* pauseButton = loadTexture("assests/images/pause.png");
SDL_Texture* resume = loadTexture("assests/images/resume.png");
SDL_Texture* returnMenu = loadTexture("assests/images/returnmenu.png");

TTF_Font* fontNum = loadFont("assests/fonts/arcadeclassic.ttf", 30);
TTF_Font* fontTitle = loadFont("assests/fonts/arcadeclassic.ttf", 40);
TTF_Font* fontCum1 = loadFont("assests/fonts/Arial.ttf", 50);
TTF_Font* fontCum2 = loadFont("assests/fonts/arcadeclassic.ttf", 45);
TTF_Font* bigFont = loadFont("assests/fonts/arcadeclassic.ttf", 60);

SDL_Texture* pausedText = renderText("PAUSED", bigFont, whiteColor);
SDL_Texture* cycText = renderText("Choose your colour", fontTitle, blackColor);
#endif // KHAIQUAT_H_INCLUDED
