#ifndef ACTIONCARD_H_INCLUDED
#define ACTIONCARD_H_INCLUDED
#include "render.h"
#include <map>

string aiChooseColour(vector<card> &player)
{
    map<string, int> mp;
    for(int i=0;i<player.size();i++) {
        mp[player[i].color] ++;
    }
    int maxx=0;
    string res;
    for(auto x:mp) {
        if(maxx<x.second) {
            res = x.first;
            maxx = x.second;
        }
    }
    if(res=="wild") res = colors[rand() % 4];
    return res;
}
string chooseYourColour(SDL_Event &event)
{
    int x, y;
    timeLeft = 500;
    while (true) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) {
            return "blue"; // để thoát khỏi hàm thôi:))
        }
        SDL_RenderClear(renderer);
        rendergame();
        renderTime();
        chooseColourScreen();
        presentScene();
        if(timeLeft==0) return colors[rand() % 4];
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
void arrangeCard(SDL_Event &event)
{
    checkSize();
    vector<Mouse> endPoint;
    vector<Mouse> u;
    for(int i=0;i<myCard.size();i++) {
        endPoint.push_back({300 + dd*i, 480});
        u.push_back({endPoint[i].x - myCard[i].x, endPoint[i].y - myCard[i].y});
    }
    for(int i=1;i<=speed;i++) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) break;
        for(int i=0;i<myCard.size();i++) {
            myCard[i].turnEast(u[i].x / speed);
            myCard[i].turnSouth(u[i].y / speed);
            myCard[i].move();
        }
        SDL_RenderClear(renderer);
        rendergame();
        presentScene();
    }
}
void prepareSwap(SDL_Event &event)
{
    Mouse endPoint = {300, 480};
    vector<Mouse> u;
    for(int i=0;i<myCard.size();i++) {
        u.push_back({endPoint.x - myCard[i].x, endPoint.y - myCard[i].y});
    }
    for(int i=1;i<=speed;i++) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) break;
        for(int i=0;i<myCard.size();i++) {
            myCard[i].turnEast(u[i].x / speed);
            myCard[i].turnSouth(u[i].y / speed);
            myCard[i].move();
        }
        SDL_RenderClear(renderer);
        rendergame();
        presentScene();
    }
}
void swaping(SDL_Event &event, Mouse pointA, Mouse pointB)
{
    Vector u(pointB.x - pointA.x, pointB.y - pointA.y);
    double deltaScaleX = pointB.scaleX - pointA.scaleX;
    double deltaScaleY = pointB.scaleY - pointA.scaleY;
    for(int j=1;j<=speed*2;j++) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) break;
        Uint32 frameStart = SDL_GetTicks();
        pointA.turnEast(u.x / (speed*2));
        pointA.turnSouth(u.y / (speed*2));
        pointB.turnWest(u.x / (speed*2));
        pointB.turnNorth(u.y / (speed*2));
        pointA.move();
        pointB.move();
        pointA.scaleX = pointA.scaleX + deltaScaleX/(speed*2);
        pointA.scaleY = pointA.scaleY + deltaScaleY/(speed*2);
        pointB.scaleX = pointB.scaleX - deltaScaleX/(speed*2);
        pointB.scaleY = pointB.scaleY - deltaScaleY/(speed*2);
        SDL_RenderClear(renderer);
        rendergame();
        getSecretCard(pointA.x, pointA.y, pointA.scaleX, pointA.scaleY);
        getSecretCard(pointB.x, pointB.y, pointB.scaleX, pointB.scaleY);
        presentScene();
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        frame = frameTime;
    }
    cout<<"frame5: "<<frame<<endl;
}
void swapAllPlayers(SDL_Event &event)
{
    Mouse point1 = {300, 480, 100, 147};
    Mouse point2 = {161, 272, 70, 103};
    Mouse point3 = {611, 47, 70, 103};
    Mouse point4 = {961.8, 272, 70, 103};
    if(numberOfPlayers==2) swaping(event, point1, point2);
    else if(numberOfPlayers==3) {
        Mouse u[3];
        u[0].x = point2.x - point1.x;
        u[0].y = point2.y - point1.y;
        u[0].scaleX = point2.scaleX - point1.scaleX;
        u[0].scaleY = point2.scaleY - point1.scaleY;
        u[1].x = point3.x - point2.x;
        u[1].y = point3.y - point2.y;
        u[2].x = point1.x - point3.x;
        u[2].y = point1.y - point3.y;
        u[2].scaleX = point1.scaleX - point3.scaleX;
        u[2].scaleY = point1.scaleY - point3.scaleY;
        if(direct) {
            for(int j=1;j<=speed*2;j++) {
                SDL_PollEvent(&event);
                Paused(event);
                if(backToMenu) break;
                point1.turnEast(u[0].x / (speed*2));
                point1.turnSouth(u[0].y / (speed*2));
                point2.turnEast(u[1].x / (speed*2));
                point2.turnSouth(u[1].y / (speed*2));
                point3.turnEast(u[2].x / (speed*2));
                point3.turnSouth(u[2].y / (speed*2));
                point1.move();
                point2.move();
                point3.move();
                point1.scaleX = point1.scaleX + u[0].scaleX/(speed*2);
                point1.scaleY = point1.scaleY + u[0].scaleY/(speed*2);
                point3.scaleX = point3.scaleX + u[2].scaleX/(speed*2);
                point3.scaleY = point3.scaleY + u[2].scaleY/(speed*2);
                SDL_RenderClear(renderer);
                rendergame();
                getSecretCard(point1.x, point1.y, point1.scaleX, point1.scaleY);
                getSecretCard(point2.x, point2.y, point2.scaleX, point2.scaleY);
                getSecretCard(point3.x, point3.y, point3.scaleX, point3.scaleY);
                presentScene();
            }
        }
        else {
            for(int j=1;j<=speed*2;j++) {
                SDL_PollEvent(&event);
                Paused(event);
                if(backToMenu) break;
                point1.turnWest(u[2].x / (speed*2));
                point1.turnNorth(u[2].y / (speed*2));
                point2.turnWest(u[0].x / (speed*2));
                point2.turnNorth(u[0].y / (speed*2));
                point3.turnWest(u[1].x / (speed*2));
                point3.turnNorth(u[1].y / (speed*2));
                point1.move();
                point2.move();
                point3.move();
                point1.scaleX = point1.scaleX - u[2].scaleX/(speed*2);
                point1.scaleY = point1.scaleY - u[2].scaleY/(speed*2);
                point2.scaleX = point3.scaleX - u[0].scaleX/(speed*2);
                point2.scaleY = point3.scaleY - u[0].scaleY/(speed*2);
                SDL_RenderClear(renderer);
                rendergame();
                getSecretCard(point1.x, point1.y, point1.scaleX, point1.scaleY);
                getSecretCard(point2.x, point2.y, point2.scaleX, point2.scaleY);
                getSecretCard(point3.x, point3.y, point3.scaleX, point3.scaleY);
                presentScene();
            }
        }
    }
    else if(numberOfPlayers==4) {
        Mouse u[4];
        u[0].x = point2.x - point1.x;
        u[0].y = point2.y - point1.y;
        u[0].scaleX = point2.scaleX - point1.scaleX;
        u[0].scaleY = point2.scaleY - point1.scaleY;
        u[1].x = point3.x - point2.x;
        u[1].y = point3.y - point2.y;
        u[2].x = point4.x - point3.x;
        u[2].y = point4.y - point3.y;
        u[3].x = point1.x - point4.x;
        u[3].y = point1.y - point4.y;
        u[3].scaleX = point1.scaleX - point4.scaleX;
        u[3].scaleY = point1.scaleY - point4.scaleY;
        if(direct) {
            for(int j=1;j<=speed*2;j++) {
                SDL_PollEvent(&event);
                Paused(event);
                if(backToMenu) break;
                point1.turnEast(u[0].x / (speed*2));
                point1.turnSouth(u[0].y / (speed*2));
                point2.turnEast(u[1].x / (speed*2));
                point2.turnSouth(u[1].y / (speed*2));
                point3.turnEast(u[2].x / (speed*2));
                point3.turnSouth(u[2].y / (speed*2));
                point4.turnEast(u[3].x / (speed*2));
                point4.turnSouth(u[3].y / (speed*2));
                point1.move();
                point2.move();
                point3.move();
                point4.move();
                point1.scaleX = point1.scaleX + u[0].scaleX/(speed*2);
                point1.scaleY = point1.scaleY + u[0].scaleY/(speed*2);
                point4.scaleX = point4.scaleX + u[3].scaleX/(speed*2);
                point4.scaleY = point4.scaleY + u[3].scaleY/(speed*2);
                SDL_RenderClear(renderer);
                rendergame();
                getSecretCard(point1.x, point1.y, point1.scaleX, point1.scaleY);
                getSecretCard(point2.x, point2.y, point2.scaleX, point2.scaleY);
                getSecretCard(point3.x, point3.y, point3.scaleX, point3.scaleY);
                getSecretCard(point4.x, point4.y, point4.scaleX, point4.scaleY);
                presentScene();
            }
        }
        else {
            for(int j=1;j<=speed*2;j++) {
                SDL_PollEvent(&event);
                Paused(event);
                if(backToMenu) break;
                point1.turnWest(u[3].x / (speed*2));
                point1.turnNorth(u[3].y / (speed*2));
                point2.turnWest(u[0].x / (speed*2));
                point2.turnNorth(u[0].y / (speed*2));
                point3.turnWest(u[1].x / (speed*2));
                point3.turnNorth(u[1].y / (speed*2));
                point4.turnWest(u[2].x / (speed*2));
                point4.turnNorth(u[2].y / (speed*2));
                point1.move();
                point2.move();
                point3.move();
                point4.move();
                point1.scaleX = point1.scaleX - u[3].scaleX/(speed*2);
                point1.scaleY = point1.scaleY - u[3].scaleY/(speed*2);
                point2.scaleX = point3.scaleX - u[0].scaleX/(speed*2);
                point2.scaleY = point3.scaleY - u[0].scaleY/(speed*2);
                SDL_RenderClear(renderer);
                rendergame();
                getSecretCard(point1.x, point1.y, point1.scaleX, point1.scaleY);
                getSecretCard(point2.x, point2.y, point2.scaleX, point2.scaleY);
                getSecretCard(point3.x, point3.y, point3.scaleX, point3.scaleY);
                getSecretCard(point4.x, point4.y, point4.scaleX, point4.scaleY);
                presentScene();
            }
        }
    }
}
int chooseRival(SDL_Event &event)
{
    int x0, y0;
    timeLeft = 500;
    SDL_Rect dstRect[3];
    dstRect[0] = {250, 300, 50, 50};
    dstRect[1] = {625, 150, 50, 50};
    dstRect[2] = {900, 300, 50, 50};
    while (true) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) break;
        SDL_GetMouseState(&x0, &y0);
        SDL_RenderClear(renderer);
        rendergame();
        SDL_RenderCopy(renderer, blackTriangle1, NULL, &dstRect[0]);
        if(numberOfPlayers>2) SDL_RenderCopy(renderer, blackTriangle, NULL, &dstRect[1]);
        if(numberOfPlayers>3) SDL_RenderCopy(renderer, blackTriangle2, NULL, &dstRect[2]);
        renderTime();
        presentScene();
        if(timeLeft==0) {
            break;
        }
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT) {
                    cout<<x0<<" "<<y0<<endl;
                    if(x0>=dstRect[0].x && x0<=dstRect[0].x + dstRect[0].w && y0>=dstRect[0].y && y0<=dstRect[0].y + dstRect[0].h) return 2;
                    else if(x0>=dstRect[1].x && x0<=dstRect[1].x + dstRect[1].w && y0>=dstRect[1].y && y0<=dstRect[1].y + dstRect[1].h) return 3;
                    else if(x0>=dstRect[2].x && x0<=dstRect[2].x + dstRect[2].w && y0>=dstRect[2].y && y0<=dstRect[2].y + dstRect[2].h) return 4;
                }
                 break;
        }
    }
    if(numberOfPlayers==2) return 2;
    else return rand() % (numberOfPlayers - 1) + 2;
}
void sevenCardAction(SDL_Event &event)
{
    int id1 = playerTurn % numberOfPlayers + 1; // id1 la nguoi dinh swap bo bai cho ai do
    int id2; // la nguoi bi swap bo bai va phai co so la bai nho nhat
    if(id1==1) {
        id2 = chooseRival(event);
    }
    else id2 = findMinOfCards(id1);
    Mouse point1 = {300, 480, 100, 147};
    Mouse point2 = {161, 272, 70, 103};
    Mouse point3 = {611, 47, 70, 103};
    Mouse point4 = {961.8, 272, 70, 103};
    if(id1==1 ||id2==1) {
        prepareSwap(event);
    }
    if(id1>1) aiWin[id1-2] = true;
    if(id2>1) aiWin[id2-2] = true;
    if(id1==1) {
        beingSwapped = true;
        if(id2==2) {
            swaping(event, point1, point2);
            swap(player1, player2);
        }
        else if(id2==3) {
            swaping(event, point1, point3);
            swap(player1, player3);
        }
        else if(id2==4) {
            swaping(event, point1, point4);
            swap(player1, player4);
        }
    }
    else if(id1==2) {
        if(id2==1) {
            beingSwapped = true;
            swaping(event, point1, point2);
            swap(player1, player2);
        }
        else if(id2==3) {
            swaping(event, point2, point3);
            swap(player2, player3);
        }
        else if(id2==4) {
            swaping(event, point2, point4);
            swap(player2, player4);
        }
    }
    else if(id1==3) {
        if(id2==1) {
            beingSwapped = true;
            swaping(event, point1, point3);
            swap(player1, player3);
        }
        else if(id2==2) {
            swaping(event, point2, point3);
            swap(player2, player3);
        }
        else if(id2==4) {
            swaping(event, point3, point4);
            swap(player3, player4);
        }
    }
    else if(id1==4) {
        if(id2==1) {
            beingSwapped = true;
            swaping(event, point1, point4);
            swap(player1, player4);
        }
        else if(id2==2) {
            swaping(event, point2, point4);
            swap(player2, player4);
        }
        else if(id2==3) {
            swaping(event, point3, point4);
            swap(player3, player4);
        }
    }
    if(id1>1) aiWin[id1-2] = false;
    if(id2>1) aiWin[id2-2] = false;
    if(id1==1||id2==1) {
        beingSwapped = false;
        myCard.clear(); //reset lai
        for(int i=0;i<player1.size();i++) {
            myCard.push_back({ 300, 480}); //lay lai toa do
        }
        arrangeCard(event);
    }
}
void zeroCardAction(SDL_Event &event)
{
    prepareSwap(event);
    beingSwapped = true;
    for(int i=0;i<3;i++) aiWin[i] = true;
    swapAllPlayers(event);
    if(numberOfPlayers==2) swap(player1, player2);
    else if(numberOfPlayers==3) {
        vector<card> tmpPlayer = player1;
        if(direct) {
            player1 = player3;
            player3 = player2;
            player2 = tmpPlayer;
        }
        else {
            player1 = player2;
            player2 = player3;
            player3 = tmpPlayer;
        }
    }
    else if(numberOfPlayers==4) {
        vector<card> tmpPlayer = player1;
        if(direct) {
            player1 = player4;
            player4 = player3;
            player3 = player2;
            player2 = tmpPlayer;
        }
        else {
            player1 = player2;
            player2 = player3;
            player3 = player4;
            player4 = tmpPlayer;
        }
    }
    for(int i=0;i<3;i++) aiWin[i] = false;
    beingSwapped = false;
    myCard.clear(); //reset lai
    for(int i=0;i<player1.size();i++) {
        myCard.push_back({ 300, 480}); //lay lai toa do
    }
    arrangeCard(event);
}
void actionCard(SDL_Event &event)
{
    if(pile.number == "skip") {
        isSkip = 1;
        nextturn();
    }
    else if(pile.number == "reverse") {
        playChunk(reverseWav);
        direct = (!direct);
        if(numberOfPlayers != 2) nextturn();
    }
    else if(pile.number == "draw2") {
        playChunk(plusingSound);
        cumlativeCards+=2;
        nextturn();
    }
    else if(pile.number == "7" && zeroSevenRule &&!gameOver()) {
        for(int i=0;i<=delayTime/2;i++) {
            SDL_PollEvent(&event);
            Paused(event);
            if(backToMenu) break;
            SDL_RenderClear(renderer);
            rendergame();
            presentScene();
        }
        sevenCardAction(event);
        nextturn();
    }
    else if(pile.number == "0" && zeroSevenRule &&!gameOver()) {
        for(int i=0;i<=delayTime/2;i++) {
            SDL_PollEvent(&event);
            Paused(event);
            if(backToMenu) break;
            SDL_RenderClear(renderer);
            rendergame();
            presentScene();
        }
        zeroCardAction(event);
        nextturn();
    }
    else if(pile.number == "change" && !gameOver()) {
        string color;
        if(abs(playerTurn) % numberOfPlayers == 0) {
            color = chooseYourColour(event);
        }
        else if(abs(playerTurn) % numberOfPlayers == 1) color = aiChooseColour(player2);
        else if(abs(playerTurn) % numberOfPlayers == 2) color = aiChooseColour(player3);
        else if(abs(playerTurn) % numberOfPlayers == 3) color = aiChooseColour(player4);
        pile.color = color;
        nextturn();
    }
    else if(pile.number == "draw4" && !gameOver()) {
        string color;
        if(abs(playerTurn) % numberOfPlayers == 0) {
            color = chooseYourColour(event);
        }
       // else color = colors[rand() % 4];
        else if(abs(playerTurn) % numberOfPlayers == 1) color = aiChooseColour(player2);
        else if(abs(playerTurn) % numberOfPlayers == 2) color = aiChooseColour(player3);
        else if(abs(playerTurn) % numberOfPlayers == 3) color = aiChooseColour(player4);
        pile.color = color;
        cumlativeCards+=4;
        nextturn();
        playChunk(plusingSound);
    }
    else nextturn();
}

#endif // ACTIONCARD_H_INCLUDED
