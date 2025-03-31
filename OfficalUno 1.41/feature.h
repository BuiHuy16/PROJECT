#ifndef FEATURE_H_INCLUDED
#define FEATURE_H_INCLUDED
#include "khaiquat.h"
void getCard(Graphics graphics, string num, string col, int x, int y)
{
    if(num=="change" || num=="draw4") col = "wild";
    char* file = new char[20];
    file[0] = 'C';
    file[1] = 'a';
    file[2] = 'r';
    file[3] = 'd';
    file[4] = 's';
    file[5] = '/';
    int i=6;
    while(i-6<col.size()) {
        file[i] = col[i-6];
        i++;
    }
    while(i-col.size()-6<num.size()) {
        file[i] = num[i-col.size()-6];
        i++;
    }
    file[i] = '.';
    file[i+1] = 'p';
    file[i+2] = 'n';
    file[i+3] = 'g';
    file[i+4] = '\0';

    SDL_Texture* aCard = graphics.loadTexture(file);
    delete[] file;
    graphics.DrawScaled(aCard, x, y, 90, 139);
}
bool checkCard(int index, card player)
{
    if(index<0) return false;
    if(cumlativeCards !=0 && pile.number[0] != player.number[index]) return false;
    if(pile.number[0] == player.number[index] || player.number[index] == "change"
           || player.number[index] == "draw4") return true;
    if(pile.color[0] == player.color[index]) return true;
    return false;
}
void nextturn()
{
    if(direct) playerTurn++;
    else playerTurn--;
}
void actionCard()
{
    if(pile.number[0] == "skip") {
        for(int i=0;i<2;i++) nextturn();
    }
    else if(pile.number[0] == "reverse") {
        direct = (!direct);
        if(numberOfPlayers != 2) nextturn();
    }
    else if(pile.number[0] == "draw2") {
        cumlativeCards+=2;
        nextturn();
    }
    else if(pile.number[0] == "change") {
        string color;
        color = colors[rand() % 4];
        if(color == "red") pile.color[0] = colors[0];
        else if(color == "blue") pile.color[0] = colors[1];
        else if(color == "yellow") pile.color[0] = colors[2];
        else if(color == "green") pile.color[0] = colors[3];
        nextturn();
    }
    else if(pile.number[0] == "draw4") {
        string color;
        color = colors[rand() % 4];
        if(color == "red") pile.color[0] = colors[0];
        else if(color == "blue") pile.color[0] = colors[1];
        else if(color == "yellow") pile.color[0] = colors[2];
        else if(color == "green") pile.color[0] = colors[3];
        cumlativeCards+=4;
        nextturn();
    }
    else nextturn();
}
#endif // FEATURE_H_INCLUDED
