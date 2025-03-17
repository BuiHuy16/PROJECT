#ifndef RENDER_H_INCLUDED
#define RENDER_H_INCLUDED
#include <iostream>
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
int randomNumber()
{
    return rand();
}
void rendergame(card p1, card p2, card p3, card p4, card pile, int numberOfPlayers)
{
    cout<<"player 1 : ";
    for(int i=0;i<p1.number.size();i++) {
        cout<<p1.number[i]<<" "<<p1.color[i]<<", ";
    }
    cout<<endl<<endl;
    cout<<"player 2 : ";
    for(int i=0;i<p2.number.size();i++) {
        cout<<p2.number[i]<<" "<<p2.color[i]<<", ";
    }
    cout<<endl<<endl;
    cout<<"             "<<pile.number[0]<<endl<<"             "<<pile.color[0]<<endl<<endl;
    if(numberOfPlayers>=3) {
        cout<<"player 3 : ";
    for(int i=0;i<p3.number.size();i++) {
        cout<<p3.number[i]<<" "<<p3.color[i]<<", ";
    }
       cout<<endl<<endl;
    }
    if(numberOfPlayers>=4) {
        cout<<"player 4 : ";
    for(int i=0;i<p4.number.size();i++) {
        cout<<p4.number[i]<<" "<<p4.color[i]<<", ";
    }
       cout<<endl;
    }
    cout<<endl<<endl;
}

#endif // RENDER_H_INCLUDED
