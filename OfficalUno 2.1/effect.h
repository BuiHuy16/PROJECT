#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED

#include "ActionCard.h"

void moveCardToPile(int index, SDL_Event &event) {
    Vector u(615 - myCard[index].x, 260 - myCard[index].y);
    cout<<"your speed: "<<speed<<endl;
    while (myCard[index].x != 615 || myCard[index].y != 260) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) break;
        Uint32 frameStart = SDL_GetTicks();
        myCard[index].turnEast(u.x / speed);
        myCard[index].turnSouth(u.y / speed);
        myCard[index].move();

        SDL_RenderClear(renderer);
        rendergame();
        presentScene();
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        frame = frameTime;
        // chỉnh delayTime và speed phù hợp với fps
        if(frame<=20) {
            delayTime=85;
          //  speed = 20;
        }
        else if(frame<=25) delayTime = 75;
        else if(frame<=29) delayTime = 50;
        else if(frame<=41)
        {
            delayTime = 45;
          //  speed = 10;
        }
        else if(frame<=50) {
            delayTime = 35;
        //    speed = 8;
        }
        else
        {
            delayTime = 25;
        //    speed = 5;
        }
    }
    cout<<"frame1: "<<frame<<endl;
    if(delayTime==85) speed = 20;
    else if(delayTime==75) speed = 16;
    else if(delayTime==45 || delayTime==50) speed = 10;
    else if(delayTime==35) speed = 8;
    else speed = 5;
}
void aiMatching(double xx, double yy, string num, string col, SDL_Event &event) {
    Mouse mouse;
    mouse.x = xx;
    mouse.y = yy;
    Vector u(615 - mouse.x, 260 - mouse.y);
    for(int j=1;j<=speed;j++) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) break;
        Uint32 frameStart = SDL_GetTicks();
        mouse.turnEast(u.x / speed);
        mouse.turnSouth(u.y / speed);
        mouse.move();

        SDL_RenderClear(renderer);
        rendergame();
        getCard(num, col, mouse.x, mouse.y);
        presentScene();
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        frame = frameTime;
    }
    cout<<"frame2: "<<frame<<endl;
}
void drawingCard(SDL_Event &event) //ham minh boc bai
{
    int n = player1.size();
    myCard.push_back({ 500, 260});
    Vector u(240 + dd*n - 500, 480 - 260);
    while(myCard[n - 1].x != 240 + dd*n || myCard[n - 1].y != 480) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) break;
        Uint32 frameStart = SDL_GetTicks();
        myCard[n-1].turnEast(u.x / speed);
        myCard[n-1].turnSouth(u.y / speed);
        myCard[n-1].move();

        SDL_RenderClear(renderer);
        rendergame();
        presentScene();
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        frame = frameTime;
    }
    cout<<"frame3: "<<frame<<endl;
    myCard[n-1].dx = 0;
    myCard[n-1].dy = 0;
}
void aiDrawing(double xx, double yy, SDL_Event &event) // ham may boc bai
{
    Mouse mouse;
    mouse.x = 495;
    mouse.y = 258;
    Vector u(xx - mouse.x, yy - mouse.y);
    double scaleX = 100;
    double scaleY = 147;
    double deltaScaleX = 70 - 100;
    double deltaScaleY = 103 - 147;
    for(int j=1;j<=speed;j++) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) break;
        Uint32 frameStart = SDL_GetTicks();
        mouse.turnEast(u.x / speed);
        mouse.turnSouth(u.y / speed);
        mouse.move();
        scaleX = scaleX + deltaScaleX/speed;
        scaleY = scaleY + deltaScaleY/speed;
        SDL_RenderClear(renderer);
        rendergame();
        getSecretCard(mouse.x, mouse.y, scaleX, scaleY);
        presentScene();
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        frame = frameTime;
    }
    cout<<"frame4: "<<frame<<endl;
}
bool isKeptCard(SDL_Event &event)
{
    int x, y;
    while (true) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) break;
        SDL_GetMouseState(&x, &y);
        SDL_RenderClear(renderer);
        rendergame();
        if(x>300 && x<370 && y>450 && y<475) { //play is black
                    play2 = renderText("PLAY", fontNum, blackColor);
                    renderTexture(play2, 300, 450);
                    keepText = renderText("KEEP", fontNum, whiteColor);
                    renderTexture(keepText, 800, 450);
                 }
        else if(x>800 && x<875 && y>450 && y<475) { // keep is black
                    play2 = renderText("PLAY", fontNum, whiteColor);
                    renderTexture(play2, 300, 450);
                    keepText = renderText("KEEP", fontNum, blackColor);
                    renderTexture(keepText, 800, 450);
                 }
        else {
                    play2 = renderText("PLAY", fontNum, whiteColor);
                    renderTexture(play2, 300, 450);
                    keepText = renderText("KEEP", fontNum, whiteColor);
                    renderTexture(keepText, 800, 450);
        }
        presentScene();

        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT) {
                    if(x>300 && x<370 && y>450 && y<475) {
                        return false;
                     }
                    if(x>800 && x<875 && y>450 && y<475) { // keep is black
                        return true;
                     }
                }
                 break;
        }
    }
}
void sortCard(int index, SDL_Event &event)
{
    if(index != player1.size() - 1) {
        while (myCard[index+1].x != 300 + dd*index) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) break;
        for(int i = index+1;i<player1.size();i++) {
            myCard[i].turnWest(10);
            myCard[i].move();
        }
        SDL_RenderClear(renderer);
        rendergame();
        presentScene();
}
    }

}
void effectMovingText(SDL_Event &event)
{
    string cumText1 = "+";
    string cumText2 = to_string(cumlativeCards);
    SDL_Texture* numOfCum1 = renderText(cumText1, fontCum1, blackColor);
    SDL_Texture* numOfCum2 = renderText(cumText2, fontCum2, blackColor);
    Vector endPoint(0, 0);
    switch (abs(playerTurn) % numberOfPlayers + 1) {
        case 1:
           endPoint.x = 200;
           endPoint.y = 510;
            break;
        case 2:
          endPoint.x = 75;
          endPoint.y = 289;
            break;
        case 3:
          endPoint.x = 525;
          endPoint.y = 64;
            break;
        case 4:
          endPoint.x = 1075;
          endPoint.y = 289;
            break;
    }
    Mouse mouse;
    mouse.x = 520;
    mouse.y = 210;
    Vector u(endPoint.x - mouse.x, endPoint.y - mouse.y);
    for(int j=1;j<=speed - 2;j++) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) break;
        mouse.turnEast(u.x / (speed - 2));
        mouse.turnSouth(u.y / (speed - 2));
        mouse.move();

        SDL_RenderClear(renderer);
        rendergame();
        renderTexture(numOfCum1, mouse.x, mouse.y);
        renderTexture(numOfCum2, mouse.x + 30, mouse.y + 5);
        presentScene();
    }
    for(int j=0;j<delayTime/2;j++) {
        SDL_PollEvent(&event);
        Paused(event);
        if(backToMenu) break;
        SDL_RenderClear(renderer);
        rendergame();
        renderTexture(numOfCum1, mouse.x, mouse.y);
        renderTexture(numOfCum2, mouse.x + 30, mouse.y + 5);
        presentScene();
    }
    SDL_DestroyTexture(numOfCum1);
    SDL_DestroyTexture(numOfCum2);
}
void yourMatch(SDL_Event &event)
{
    bool canMatch = false;
    for(int i=0;i<player1.size();i++) {
        if(checkCard(i, player1)) {
            canMatch = true;
            break;
        }
    }
    int index = -1;
    int mous = -1;
    int x, y;
    bool flag = true;
    while (flag) {
        SDL_PollEvent(&event);
        SDL_GetMouseState(&x, &y);
        mous = (x-300)/dd;
        SDL_RenderClear(renderer);
        for(int i=0;i<myCard.size();i++) {
            if(i==mous && y>=480 && y<=619) myCard[i].y -= 15;
            else if(x>=myCard[player1.size() - 1].x && x<= 90 + myCard[player1.size() - 1].x && i==myCard.size() - 1 && y>=480 && y<=619)
                 myCard[i].y -=15;
        }
        rendergame();
        if(cumlativeCards==0 && !canMatch) renderArrow();
        presentScene();
        Paused(event);
        for(int i=0;i<myCard.size();i++) {
            if(myCard[i].y==465) myCard[i].y += 15;
        }
        if(!canMatch && cumlativeCards!=0) { // mình phải bốc nhiều lá vì ko có lá cộng
            for(int i=0;i<delayTime/2;i++) {
                SDL_PollEvent(&event);
                Paused(event);
                if(backToMenu) break;
                SDL_RenderClear(renderer);
                rendergame();

                presentScene();
            }
            showCumText = false;
            effectMovingText(event);
            for(int i=0;i<cumlativeCards;i++) {
                drawCard(player1);
                drawingCard(event);
            }
            showCumText = true;
            cumlativeCards=0;
            nextturn();
            SDL_RenderClear(renderer);
            flag = false;
            break;
        }
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT) {
                 if(y>=480 && y<=619)
                 {
                     index = (x-300)/dd;
                     if(x>=myCard[player1.size() - 1].x && x<= 90 + myCard[player1.size() - 1].x) index = player1.size() - 1;
                     if(checkCard(index, player1)) {
                        moveCardToPile(index, event);
                        sortCard(index, event);
                        pile.number = player1[index].number;
                        tmpColor = pile.color;
                        pile.color = player1[index].color;
                        player1.erase(player1.begin() + index , player1.begin() + index+1);
                        myCard.erase(myCard.begin() + index , myCard.begin() + index+1);
                        actionCard(event);
                        SDL_RenderClear(renderer);
                        flag = false;
                     }
                 }
                 else if(x>=500 && x<=590 && y>=260 && y<=399) {
                    if(cumlativeCards == 0) {
                        drawCard(player1);
                        drawingCard(event);
                        if(drawToMatch) {
                            if(frame<=45) {
                                for(int i=0;i<=delayTime/2;i++) {
                                    SDL_PollEvent(&event);
                                    Paused(event);
                                    if(backToMenu) break;
                                    SDL_RenderClear(renderer);
                                    rendergame();
                                    presentScene();
                                }
                            }
                            while(!checkCard(player1.size() - 1, player1)) {
                                SDL_PollEvent(&event);
                                Paused(event);
                                if(backToMenu) break;
                                drawCard(player1);
                                drawingCard(event);
                                if(frame<=45) {
                                    for(int i=0;i<=delayTime/2;i++) {
                                        SDL_PollEvent(&event);
                                        Paused(event);
                                        if(backToMenu) break;
                                        SDL_RenderClear(renderer);
                                        rendergame();
                                        presentScene();
                                    }
                                }
                                if(backToMenu) break;
                            }
                        }
                        if(checkCard(player1.size() - 1, player1)) {
                                bool answer;
                                if(!forcePLay) answer = isKeptCard(event);
                                else {
                                    answer = false;
                                    for(int i=0;i<=delayTime/3;i++) {
                                        SDL_PollEvent(&event);
                                        Paused(event);
                                        if(backToMenu) break;
                                        SDL_RenderClear(renderer);
                                        rendergame();
                                        presentScene();
                                    }
                                }
                                if(!answer) {
                                    moveCardToPile(player1.size() - 1, event);
                                    pile.number = player1[player1.size() - 1].number;
                                    tmpColor = pile.color;
                                    pile.color = player1[player1.size() - 1].color;
                                    player1.pop_back();
                                    myCard.pop_back();
                                    actionCard(event);
                                    SDL_RenderClear(renderer);
                                }
                                else nextturn();
                               }
                               else nextturn();
                        }
                    else {
                        showCumText = false;
                        effectMovingText(event);
                        for(int i=0;i<cumlativeCards;i++) {
                            drawCard(player1);
                            drawingCard(event);
                        }
                        showCumText = true;
                        cumlativeCards=0;
                        nextturn();
                    }
                    SDL_RenderClear(renderer);
                    flag = false;
                 }
                 else cout<<"lmao"<<endl;
                }
                 break;
        }
        if(backToMenu) break;
    }
}
void aiMatch(vector<card> &player, double x, double y, SDL_Event &event)
{
    vector<int> indexList;
    int index=-1;
    for(int i=0;i<player.size();i++) {
        if(checkCard(i, player)) {
            indexList.push_back(i);
        }
    }
    if(indexList.size() != 0) index = indexList[rand() % indexList.size()];
    if(index == -1) {
        if(cumlativeCards == 0) {
        drawCard(player);
        aiDrawing(x, y, event);
        if(drawToMatch) {
            if(frame<=45) {
                for(int i=0;i<=delayTime/2;i++) {
                    SDL_PollEvent(&event);
                    Paused(event);
                    if(backToMenu) break;
                    SDL_RenderClear(renderer);
                    rendergame();
                    presentScene();
                }
            }
            while(!checkCard(player.size() - 1, player)) {
                SDL_PollEvent(&event);
                drawCard(player);
                aiDrawing(x, y, event);
                if(backToMenu) break;
                if(frame<=45) {
                    for(int i=0;i<=delayTime/2;i++) {
                        SDL_PollEvent(&event);
                        Paused(event);
                        if(backToMenu) break;
                        SDL_RenderClear(renderer);
                        rendergame();
                        presentScene();
                    }
                }
                if(backToMenu) break;
            }
        }
        if(pile.number == player[player.size() - 1].number
           || pile.color == player[player.size() - 1].color
           || player[player.size() - 1].number == "change"
           || player[player.size() - 1].number == "draw4") {
            int answer = 1;
            if(answer==1) {
                //SDL_Delay(200);
                for(int i=0;i<delayTime/5;i++) {
                    SDL_PollEvent(&event);
                    Paused(event);
                    if(backToMenu) break;
                    SDL_RenderClear(renderer);
                    rendergame();

                    presentScene();
                }
                aiMatching(x, y, player[player.size() - 1].number, player[player.size() - 1].color, event);
                pile.number = player[player.size() - 1].number;
                pile.color = player[player.size() - 1].color;
                player.pop_back();
                actionCard(event);
            }
            else nextturn();
           }
           else nextturn();
        }
        else {
            showCumText = false;
            effectMovingText(event);
            for(int i=0;i<cumlativeCards;i++) {
                drawCard(player);
                aiDrawing(x, y, event);
            }
            showCumText = true;
            cumlativeCards=0;
            nextturn();
        }
        SDL_RenderClear(renderer);
    }
    else {
        int ai = abs(playerTurn) % numberOfPlayers - 1;
        if(player.size()==1) aiWin[ai] = true;
        aiMatching(x, y, player[index].number, player[index].color, event);
        pile.number = player[index].number;
        pile.color = player[index].color;
        player.erase(player.begin() + index, player.begin() + index + 1);
        actionCard(event);
        SDL_RenderClear(renderer);
    }
}

#endif // EFFECT_H_INCLUDED
