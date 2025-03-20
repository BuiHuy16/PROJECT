#ifndef KHAIQUAT_H_INCLUDED
#define KHAIQUAT_H_INCLUDED
#include <iostream>
#include <vector>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "graphics.h"

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
card player1,player2,player3,player4,pile;

SDL_Color whiteColor = {255, 255, 255, 255};
SDL_Color blackColor = {0, 0, 0, 255};
SDL_Color blueColor = {100, 100, 255, 255};
SDL_Color greenColor = {0, 255, 0, 255};
SDL_Color redColor = {255, 0, 0, 255};
SDL_Color yellowColor = {255, 255, 0, 255};

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




#endif // KHAIQUAT_H_INCLUDED
