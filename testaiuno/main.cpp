#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <ctype.h>
#include <time.h>
#include "render.h"
#include "danhBai.h"
#include "fuc.h"

using namespace std;

int main()
{
   int numberOfPlayers;
    cout<<"Enter number of players: ";
    cin>>numberOfPlayers;
    srand(time(0));
    card player1,player2,player3,player4,pile;
    for(int i=0;i<7;i++) drawCard(player1);
    for(int i=0;i<7;i++) drawCard(player2);
    drawCard(player3);
    drawCard(player4);
    if(numberOfPlayers>=3) for(int i=1;i<7;i++) drawCard(player3);
    if(numberOfPlayers>=4) for(int i=1;i<7;i++) drawCard(player4);
    drawCard(pile);
    if(pile.color[0]=="Wild") pile.color[0] = colors[randomNumber() % 4];
    while(player1.number.size() !=0 && player2.number.size() !=0 && player3.number.size() !=0 && player4.number.size() !=0) { //gameloop
        switch (abs(playerTurn) % numberOfPlayers + 1) {
            case 1:
                rendergame(player1, player2, player3, player4, pile, numberOfPlayers);
                playerDanhBai(player1, pile, numberOfPlayers);
                break;
            case 2:
                rendergame(player1, player2, player3, player4, pile, numberOfPlayers);
                ai(player2, pile, numberOfPlayers);
                break;
            case 3:
                rendergame(player1, player2, player3, player4, pile, numberOfPlayers);
                ai(player3, pile, numberOfPlayers);
                break;
            case 4:
                rendergame(player1, player2, player3, player4, pile, numberOfPlayers);
                ai(player4, pile, numberOfPlayers);
                break;
        }
    }
    if(abs(playerTurn) % numberOfPlayers == 0) cout<<"Player "<<numberOfPlayers<<" won";
    else cout<<"Player "<<abs(playerTurn) % numberOfPlayers<<" won";
    return 0;
}
