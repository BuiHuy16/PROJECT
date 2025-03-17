#ifndef DANHBAI_H_INCLUDED
#define DANHBAI_H_INCLUDED
#include "render.h"
#include "fuc.h"
void playerDanhBai(card &player, card &pile, int numberOfPlayers)
{
    cout<<"Turn: player "<<abs(playerTurn) % numberOfPlayers + 1<<endl;
    int index=1;
    while(index!=0) {
        cout<<"Enter your index number (enter 0 to draw card): ";
        cin>>index;
        if(cumlativeCards !=0 && pile.number[0] != player.number[index - 1]) continue;
        if(pile.number[0] == player.number[index - 1] || player.number[index - 1] == "Wild"
           || player.number[index - 1] == "Wild +4") break;
        if(pile.color[0] == player.color[index - 1]) break;
    }
    cout<<endl;
    if(index==0) {
        if(cumlativeCards == 0) {
        drawCard(player);
        if(pile.number[0] == player.number[player.number.size() - 1]
           || pile.color[0] == player.color[player.color.size() - 1]
           || player.color[player.color.size() - 1] == "Wild"
           || player.color[player.color.size() - 1] == "Wild +4") {
            int answer=2;
            cout<<"Do you want to play this card? "<<endl<<"Enter 1 to play or else enter 0: ";
            while(answer!=0 && answer != 1) {
                cin>>answer;
            }
            if(answer==1) {
                pile.number[0] = player.number[player.number.size() - 1];
                pile.color[0] = player.color[player.color.size() - 1];
                player.number.pop_back();
                player.color.pop_back();
                actionCard(pile, numberOfPlayers);
            }
            else nextturn();
           }
           else nextturn();
        }
        else {
            for(int i=0;i<cumlativeCards;i++) drawCard(player);
            cumlativeCards=0;
            nextturn();
        }
    }
    else {
        pile.number[0] = player.number[index - 1];
        pile.color[0] = player.color[index - 1];
        player.number.erase(player.number.begin() + index - 1, player.number.begin() + index);
        player.color.erase(player.color.begin() + index - 1, player.color.begin() + index);
        actionCard(pile, numberOfPlayers);
    }
}
void ai(card &player, card &pile, int numberOfPlayers)
{
    vector<int> indexList;
    cout<<"Turn: player "<<abs(playerTurn) % numberOfPlayers + 1<<endl<<endl;
    size_t index=0;
    for(size_t i=0;i<player.number.size();i++) {
        if(cumlativeCards !=0 && pile.number[0] != player.number[i]) continue;
        else {
            if(pile.number[0] == player.number[i] || player.number[i] == "Wild"
           || player.number[i] == "Wild +4") indexList.push_back(i);
        else if(pile.color[0] == player.color[i]) indexList.push_back(i);
        }
    }
    if(indexList.size() != 0) index = indexList[randomNumber() % indexList.size()] + 1; //thu tu la bai tu so 1
    if(index == 0) {
        if(cumlativeCards == 0) {
        drawCard(player);
        if(pile.number[0] == player.number[player.number.size() - 1]
           || pile.color[0] == player.color[player.color.size() - 1]
           || player.color[player.color.size() - 1] == "Wild"
           || player.color[player.color.size() - 1] == "Wild +4") {
            int answer = 1;
            if(answer==1) {
                pile.number[0] = player.number[player.number.size() - 1];
                pile.color[0] = player.color[player.color.size() - 1];
                player.number.pop_back();
                player.color.pop_back();
                actionCard(pile, numberOfPlayers);
            }
            else nextturn();
           }
           else nextturn();
        }
        else {
            for(int i=0;i<cumlativeCards;i++) drawCard(player);
            cumlativeCards=0;
            nextturn();
        }
    }
    else {
        pile.number[0] = player.number[index - 1];
        pile.color[0] = player.color[index - 1];
        player.number.erase(player.number.begin() + index - 1, player.number.begin() + index);
        player.color.erase(player.color.begin() + index - 1, player.color.begin() + index);
        actionCard(pile, numberOfPlayers);
    }
}

#endif // DANHBAI_H_INCLUDED
