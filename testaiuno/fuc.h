#ifndef FUC_H_INCLUDED
#define FUC_H_INCLUDED
#include"render.h"
void drawCard(card &player)
{
    int wild = randomNumber() % 10;
    if(wild != 3) {
        player.number.push_back(numbers[randomNumber() % 13]);
        player.color.push_back(colors[randomNumber() % 4]);
    }
    else {
        player.number.push_back(specialCards[randomNumber() % 2]);
        player.color.push_back(specialCards[0]);
    }
}
void nextturn()
{
    if(direct) playerTurn++;
    else playerTurn--;
}
void actionCard(card &pile, int numberOfPlayers)
{
    if(pile.number[0] == "Skip") {
        for(int i=0;i<2;i++) nextturn();
    }
    else if(pile.number[0] == "Reverse") {
        direct = (!direct);
        if(numberOfPlayers != 2) nextturn();
    }
    else if(pile.number[0] == "+2") {
        cumlativeCards+=2;
        nextturn();
    }
    else if(pile.number[0] == "Wild") {
        string color;
        if(abs(playerTurn) % numberOfPlayers == 0) {
            cout<<"Choose a color: ";
            cin>>color;
        }
        else color = colors[randomNumber() % 4];
        for(int i=0;i<color.size();i++) color[i] = tolower(color[i]);
        if(color == "red") pile.color[0] = colors[0];
        else if(color == "blue") pile.color[0] = colors[1];
        else if(color == "yellow") pile.color[0] = colors[2];
        else if(color == "green") pile.color[0] = colors[3];
        nextturn();
    }
    else if(pile.number[0] == "Wild +4") {
        string color;
        if(abs(playerTurn) % numberOfPlayers == 0) {
            cout<<"Choose a color: ";
            cin>>color;
        }
        else color = colors[randomNumber() % 4];
        for(int i=0;i<color.size();i++) color[i] = tolower(color[i]);
        if(color == "red") pile.color[0] = colors[0];
        else if(color == "blue") pile.color[0] = colors[1];
        else if(color == "yellow") pile.color[0] = colors[2];
        else if(color == "green") pile.color[0] = colors[3];
        cumlativeCards+=4;
        nextturn();
    }
    else nextturn();
}

#endif // FUC_H_INCLUDED
