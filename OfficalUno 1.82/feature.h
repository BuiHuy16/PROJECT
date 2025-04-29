#ifndef FEATURE_H_INCLUDED
#define FEATURE_H_INCLUDED
#include "screen.h"

SDL_Texture*  getCard(string num, string col)
{
    if(num=="change" || num=="draw4") col = "wild";
    string file = "Cards/" + col + num + ".png";

    SDL_Texture* aCard = loadTexture(file);
    return aCard;
}
bool checkCard(int index, vector<card> player)
{
    if(index<0 || index>=player.size()) return false;
    if(cumlativeCards !=0 && pile.number != player[index].number) return false;
    if(pile.number == player[index].number || player[index].number == "change"
           || player[index].number == "draw4") return true;
    if(pile.color == player[index].color) return true;
    return false;
}
void nextturn()
{
    if(direct) playerTurn++;
    else playerTurn--;
    if(abs(playerTurn) % numberOfPlayers==0) playerTurn = 12;
}
void actionCard(SDL_Texture* pileImage)
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
            color = chooseYourColour();
        }
        else color = colors[rand() % 4];
        if(color == "red") pile.color = colors[0];
        else if(color == "blue") pile.color = colors[1];
        else if(color == "yellow") pile.color = colors[2];
        else if(color == "green") pile.color = colors[3];
        nextturn();
    }
    else if(pile.number == "draw4") {
        string color;
        if(abs(playerTurn) % numberOfPlayers == 0) {
            color = chooseYourColour();
        }
        else color = colors[rand() % 4];
        if(color == "red") pile.color = colors[0];
        else if(color == "blue") pile.color = colors[1];
        else if(color == "yellow") pile.color = colors[2];
        else if(color == "green") pile.color = colors[3];
        cumlativeCards+=4;
        nextturn();
    }
    else nextturn();
}

void resetFeature()
{
    direct = true;
    playerTurn = 12;
    cumlativeCards = 0;
    isSkip = 0;
    player1.clear();
    player2.clear();
    player3.clear();
    player4.clear();
    myCard.clear();
}
#endif // FEATURE_H_INCLUDED
