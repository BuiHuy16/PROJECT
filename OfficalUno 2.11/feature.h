#ifndef FEATURE_H_INCLUDED
#define FEATURE_H_INCLUDED
#include "screen.h"
void checkSize()
{
    if(player1.size()>30) dd = 25;
    else if(player1.size()>22) dd = 30;
    else if(player1.size()>19) dd = 35;
    else if(player1.size()>16) dd = 40;
    else if(player1.size()>13) dd = 45;
    else if(player1.size()>11) dd = 50;
    else if(player1.size()>9) dd = 55;
    else dd = 60;
}
int findIndex(const string arr[], string key, int n)
{
    int index=0;
    for(int i=0;i<n;i++) {
        if(arr[i] == key) {
            index = i;
            break;
        }
    }
    return index;
}
void getCard(string num, string col, double x0, double y0) //ve la bai
{
    int indexNum, indexCol, index;
    if(num != "change" && num != "draw4") {
        indexNum = findIndex(numbers, num, 13);
        indexCol = findIndex(colors, col, 4);
        index = 12 + indexNum + 13*indexCol;
    }
    else {
        if(num=="change") {
            if(col=="wild") index = 1;
            else index = 2 + findIndex(colors, col, 4);
        }
        else if(num=="draw4") {
            if(col=="wild") index = 6;
            else index = 7 + findIndex(colors, col, 4);
        }
    }
    double xx = 104.9;
    double yy = 161.6;
    int aa = index % 12;
    int bb = index / 12;
    SDL_Rect srcRect = { xx*aa, yy*bb, xx, yy};
    SDL_Rect dstRect = { x0, y0, 90, 139 };
    SDL_RenderCopy(renderer, secretCards, &srcRect, &dstRect);
}
void getSecretCard(double x0, double y0, double w0, double h0)
{
    SDL_Rect dstRect = { x0, y0, w0, h0};
    SDL_RenderCopy(renderer, secretCard, NULL, &dstRect);
}
bool checkCard(int index, vector<card> player)
{
    if(index<0 || index>=player.size()) return false;
    if(cumlativeCards !=0 && !isStacked) return false;
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
void getNameOfPlayer()
{
	vector<string> wordList;
	ifstream file("listname.txt");
  	if (file.is_open()) {
	    string word;
		while(file> word) {
            wordList.push_back(word);
        }
    	file.close();
  	}
  	if (wordList.size() > 0) {
    	for(int i=1;i<numberOfPlayers;i++) {
            int randomIndex = rand() % wordList.size();
            namePlayer.push_back(wordList[randomIndex]);
            wordList.erase(wordList.begin() + randomIndex, wordList.begin() + randomIndex + 1);
    	}
	}
}
void resetFeature()
{
    direct = true;
    playerTurn = 12;
    cumlativeCards = 0;
    isSkip = 0;
    showCumText = true;
    for(int i=0;i<3;i++) aiWin[i] = false;
    player1.clear();
    player2.clear();
    player3.clear();
    player4.clear();
    myCard.clear();
    namePlayer.clear();
}
#endif // FEATURE_H_INCLUDED
