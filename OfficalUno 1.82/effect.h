#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED

#include "render.h"
#define speed 10
void moveCardToPile(int index, SDL_Texture* pileImage, SDL_Event &event) {
    Vector u(615 - myCard[index].x, 260 - myCard[index].y);
    while (myCard[index].x != 615 || myCard[index].y != 260) {
    SDL_PollEvent(&event);
    Uint32 frameStart = SDL_GetTicks();

    myCard[index].turnEast(u.x / speed);
    myCard[index].turnSouth(u.y / speed);
    myCard[index].move();

    SDL_RenderClear(renderer);
    rendergame();
    DrawScaled( pileImage, 615, 260, 90, 139);
        for(int i=0;i<myCard.size();i++) {
            DrawScaled( myCard[i].texture, myCard[i].x, myCard[i].y, 90, 139);
        }
    presentScene();

    Uint32 frameTime = SDL_GetTicks() - frameStart;
    cout<<"frame: "<<frameTime<<endl;
    SDL_Delay(0);
}
}
void aiMatching(SDL_Texture* pileImage, double xx, double yy, string num, string col, SDL_Event &event) {
    Mouse mouse;
    mouse.x = xx;
    mouse.y = yy;
    Vector u(615 - mouse.x, 260 - mouse.y);
    SDL_Texture* aiCard = getCard(num, col);
    for(int j=1;j<=speed;j++) {
        SDL_PollEvent(&event);
        mouse.turnEast(u.x / speed);
        mouse.turnSouth(u.y / speed);
        mouse.move();

        SDL_RenderClear(renderer);
        rendergame();
        DrawScaled( pileImage, 615, 260, 90, 139);
            for(int i=0;i<myCard.size();i++) {
                DrawScaled( myCard[i].texture, myCard[i].x, myCard[i].y, 90, 139);
            }
        DrawScaled(aiCard, mouse.x, mouse.y, 90, 139);
        presentScene();
        SDL_Delay(0);
    }
    SDL_DestroyTexture(aiCard);
}
void drawingCard(SDL_Texture* pileImage, SDL_Event &event) //ham minh boc bai
{
    int n = player1.size();
    SDL_Texture* myHand = getCard(player1[n - 1].number, player1[n - 1].color);
    myCard.push_back({ 500, 260, myHand });
    Vector u(240 + 60*n - 500, 480 - 260);
    while(myCard[n - 1].x != 240 + 60*n || myCard[n - 1].y != 480) {
        SDL_PollEvent(&event);
        myCard[n-1].turnEast(u.x / speed);
        myCard[n-1].turnSouth(u.y / speed);
        myCard[n-1].move();

        SDL_RenderClear(renderer);
        rendergame();
        DrawScaled( pileImage, 615, 260, 90, 139);
            for(int i=0;i<myCard.size();i++) {
                DrawScaled( myCard[i].texture, myCard[i].x, myCard[i].y, 90, 139);
            }
        presentScene();
        SDL_Delay(0);
    }
    //SDL_DestroyTexture(myHand);
    myCard[n-1].dx = 0;
    myCard[n-1].dy = 0;
}
void aiDrawing(SDL_Texture* pileImage, double xx, double yy, SDL_Event &event) // ham may boc bai
{
    Mouse mouse;
    mouse.x = 500;
    mouse.y = 260;
    Vector u(xx - mouse.x, yy - mouse.y);
    double scaleX = 90;
    double scaleY = 139;
    double deltaScaleX = 67.2 - 90;
    double deltaScaleY = 104.4 - 139;
    SDL_Texture* aiCard = loadTexture("Cards/secretcard.png");
    for(int j=1;j<=speed;j++) {
        SDL_PollEvent(&event);
        mouse.turnEast(u.x / speed);
        mouse.turnSouth(u.y / speed);
        mouse.move();
        scaleX = scaleX + deltaScaleX/speed;
        scaleY = scaleY + deltaScaleY/speed;
        SDL_RenderClear(renderer);
        rendergame();
        DrawScaled( pileImage, 615, 260, 90, 139);
            for(int i=0;i<myCard.size();i++) {
                DrawScaled( myCard[i].texture, myCard[i].x, myCard[i].y, 90, 139);
            }
        DrawScaled(aiCard, mouse.x, mouse.y, scaleX, scaleY);
        presentScene();
        SDL_Delay(0);
    }
    SDL_DestroyTexture(aiCard);
}
bool isKeptCard(SDL_Texture* pileImage, SDL_Event &event)
{
    TTF_Font* font = loadFont("arcadeclassic.ttf", 30);

    int x, y;
    while (true) {
        SDL_PollEvent(&event);
        SDL_GetMouseState(&x, &y);
        SDL_RenderClear(renderer);
        rendergame();
        DrawScaled( pileImage, 615, 260, 90, 139);
        for(int i=0;i<myCard.size();i++) {
            DrawScaled( myCard[i].texture, myCard[i].x, myCard[i].y, 90, 139);
        }
        if(x>300 && x<370 && y>450 && y<475) { //play is black
                    play2 = renderText("PLAY", font, blackColor);
                    renderTexture(play2, 300, 450);
                    keepText = renderText("KEEP", font, whiteColor);
                    renderTexture(keepText, 800, 450);
                 }
        else if(x>800 && x<875 && y>450 && y<475) { // keep is black
                    play2 = renderText("PLAY", font, whiteColor);
                    renderTexture(play2, 300, 450);
                    keepText = renderText("KEEP", font, blackColor);
                    renderTexture(keepText, 800, 450);
                 }
        else {
                    play2 = renderText("PLAY", font, whiteColor);
                    renderTexture(play2, 300, 450);
                    keepText = renderText("KEEP", font, whiteColor);
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
        while (myCard[index+1].x != 300 + 60*index) {
        SDL_PollEvent(&event);
        Uint32 frameStart = SDL_GetTicks();
        for(int i = index+1;i<player1.size();i++) {
            myCard[i].turnWest(10);
            myCard[i].move();
        }
        SDL_RenderClear(renderer);
        rendergame();
            for(int i=0;i<myCard.size();i++) {
                DrawScaled( myCard[i].texture, myCard[i].x, myCard[i].y, 90, 139);
            }
        presentScene();

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        cout<<"frame: "<<frameTime<<endl;
        SDL_Delay(0);
}
    }

}
void yourMatch(SDL_Texture* pileImage, SDL_Event &event)
{
    int index = -1;

    int x, y;
    bool flag = true;
    while (flag) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&x, &y);
                 if(y>=480 && y<=619)
                 {
                     index = (x-300)/60;
                     if(checkCard(index, player1)) {
                    moveCardToPile(index, pileImage, event);
                    sortCard(index, event);
                    pile.number = player1[index].number;
                    pile.color = player1[index].color;
                    player1.erase(player1.begin() + index , player1.begin() + index+1);
                    myCard.erase(myCard.begin() + index , myCard.begin() + index+1);
                    actionCard(pileImage);
                    SDL_RenderClear(renderer);
                    flag = false;
                 }
                 }

                 else if(x>=500 && x<=590 && y>=260 && y<=399) {
                    if(cumlativeCards == 0) {
                        drawCard(player1);
                        drawingCard(pileImage, event);
                        if(checkCard(player1.size() - 1, player1)) {
                                bool answer = isKeptCard(pileImage, event);
                                if(!answer) {
                                    moveCardToPile(player1.size() - 1, pileImage, event);
                                    pile.number = player1[player1.size() - 1].number;
                                    pile.color = player1[player1.size() - 1].color;
                                    player1.pop_back();
                                    myCard.pop_back();
                                    actionCard(pileImage);
                                    SDL_RenderClear(renderer);
                                }
                                else nextturn();
                               }
                               else nextturn();
                        }
                    else {
                        for(int i=0;i<cumlativeCards;i++) {
                            drawCard(player1);
                            drawingCard(pileImage, event);
                        }
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
    }
}
void aiMatch(SDL_Texture* pileImage, vector<card> &player, double x, double y, SDL_Event &event)
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
        aiDrawing(pileImage, x, y, event);
        if(pile.number == player[player.size() - 1].number
           || pile.color == player[player.size() - 1].color
           || player[player.size() - 1].color == "change"
           || player[player.size() - 1].color == "draw4") {
            int answer = 1;
            if(answer==1) {
                SDL_Delay(200);
                aiMatching(pileImage, x, y, player[player.size() - 1].number, player[player.size() - 1].color, event);
                pile.number = player[player.size() - 1].number;
                pile.color = player[player.size() - 1].color;
                player.pop_back();
                actionCard(pileImage);
            }
            else nextturn();
           }
           else nextturn();
        }
        else {
            for(int i=0;i<cumlativeCards;i++) {
                drawCard(player);
                aiDrawing(pileImage, x, y, event);
            }
            cumlativeCards=0;
            nextturn();
        }
        SDL_RenderClear(renderer);
    }
    else {
        aiMatching(pileImage, x, y, player[index].number, player[index].color, event);
        pile.number = player[index].number;
        pile.color = player[index].color;
        player.erase(player.begin() + index, player.begin() + index + 1);
        actionCard(pileImage);
        SDL_RenderClear(renderer);
    }
}

#endif // EFFECT_H_INCLUDED
