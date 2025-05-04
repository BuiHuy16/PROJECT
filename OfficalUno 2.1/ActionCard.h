#ifndef ACTIONCARD_H_INCLUDED
#define ACTIONCARD_H_INCLUDED
#include "render.h"

string chooseYourColour(SDL_Event &event)
{
    int x, y;
    while (true) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) {
            return "blue"; // để thoát khỏi hàm thôi:))
        }
        SDL_RenderClear(renderer);
        rendergame();
        chooseColourScreen();
        presentScene();
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&x, &y);
                 if(x>=500 && x<=600) {
                    if(y>=225 && y<=325) return "blue";
                    else if(y>=325 && y<=425) return "red";
                 }
                 else if(x>=600 && x<=700) {
                    if(y>=225 && y<=325) return "green";
                    else if(y>=325 && y<=425) return "yellow";
                 }
                }
                 break;
        }
    }
}

void actionCard(SDL_Event &event)
{
    if(pile.number == "skip") {
        isSkip = 1;
        nextturn();
    }
    else if(pile.number == "reverse") {
        direct = (!direct);
        if(numberOfPlayers != 2) nextturn();
    }
    else if(pile.number == "draw2") {
        cumlativeCards+=2;
        nextturn();
    }
    else if(pile.number == "change") {
        string color;
        if(abs(playerTurn) % numberOfPlayers == 0) {
            color = chooseYourColour(event);
        }
        else color = colors[rand() % 4];
        pile.color = color;
        nextturn();
    }
    else if(pile.number == "draw4") {
        string color;
        if(abs(playerTurn) % numberOfPlayers == 0) {
            color = chooseYourColour(event);
        }
        else color = colors[rand() % 4];
        pile.color = color;
        cumlativeCards+=4;
        nextturn();
    }
    else nextturn();
}

#endif // ACTIONCARD_H_INCLUDED
