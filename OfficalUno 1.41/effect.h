#ifndef EFFECT_H_INCLUDED
#define EFFECT_H_INCLUDED

#include "render.h"
struct Mouse {
    int x, y;
    int dx = 0, dy = 0;
    void move() {
        x += dx;
        y += dy;
    }
    void turnNorth(float speed) {
        dy = -speed;
    }
    void turnSouth(float speed) {
        dy = speed;
    }
    void turnWest(float speed) {
        dx = -speed;
    }
    void turnEast(float speed) {
        dx = speed;
    }
};
void rendermove(Mouse &mouse, Graphics graphics, int index)
{
    //getCard(graphics, player1.number[index], player1.color[index], mouse.x, mouse.y);
}
void moveCardToPile(Graphics graphics, int index) {
    Mouse mouse;
    mouse.x = 300 + index*60;
    mouse.y = 480;
    float speedX = 500.0f;
    float speedY = (speedX*220)/(abs(315-60*index));
    Uint32 lastTime = SDL_GetTicks();
    while (mouse.x != 615 || mouse.y != 260) {
        SDL_RenderClear(graphics.renderer);
       // rendergame(graphics, player1, player2, player3, player4);
   // renderYourCard(graphics, -1, player1);

        Uint32 currentTime = SDL_GetTicks();
        float deltaTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        mouse.turnEast(speedX*deltaTime);
        mouse.turnNorth(speedY*deltaTime);
        mouse.move();

        rendermove(mouse, graphics, index);
        graphics.presentScene();
    }
}
void yourMatch(Graphics graphics, card &player1)
{
    int index = -1;
    SDL_Event event;
    int x, y;
    bool flag = true;
    while (flag) {
        SDL_GetMouseState(&x, &y);
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONDOWN:
                 cerr << "(cc) Down at (" << x << ", " << y << ")\n";
                 break;
            case SDL_MOUSEBUTTONUP:
                 cerr << "(cc) Up at (" << x << ", " << y << ")\n";
                 if(y>=480 && y<=619) index = (x-300)/60;
                 if(checkCard(index, player1)) {
                    //moveCardToPile(graphics, index);
                    //
                    pile.number[0] = player1.number[index];
                    pile.color[0] = player1.color[index];
                    player1.number.erase(player1.number.begin() + index , player1.number.begin() + index+1);
                    player1.color.erase(player1.color.begin() + index, player1.color.begin() + index+1);
                    actionCard();
                    SDL_RenderClear(graphics.renderer);
                    flag = false;
                    //actionCard(pile, numberOfPlayers);
                 }
                 else if(x>=500 && x<=590 && y>=260 && y<=399) {
                    if(cumlativeCards == 0) {
                        drawCard(player1);
                        nextturn();
        }
                    else {
                        for(int i=0;i<cumlativeCards;i++) drawCard(player1);
                        cumlativeCards=0;
                        nextturn();
                    }
                    SDL_RenderClear(graphics.renderer);
                    flag = false;
                 }
                 break;
        }
        SDL_Delay(150);
    }
}
void aiMatch(Graphics graphics, card &player)
{
    vector<int> indexList;
    int index=-1;
    for(int i=0;i<player.number.size();i++) {
        if(checkCard(i, player)) {
            indexList.push_back(i);
        }
    }
    if(indexList.size() != 0) index = indexList[rand() % indexList.size()];
    cerr<<index<<endl;
    if(index == -1) {
        if(cumlativeCards == 0) {
        drawCard(player);
        if(pile.number[0] == player.number[player.number.size() - 1]
           || pile.color[0] == player.color[player.color.size() - 1]
           || player.color[player.color.size() - 1] == "change"
           || player.color[player.color.size() - 1] == "draw4") {
            int answer = 1;
            if(answer==1) {
                pile.number[0] = player.number[player.number.size() - 1];
                pile.color[0] = player.color[player.color.size() - 1];
                player.number.pop_back();
                player.color.pop_back();
                actionCard();
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
        SDL_RenderClear(graphics.renderer);
    }
    else {
        pile.number[0] = player.number[index];
        pile.color[0] = player.color[index];
        player.number.erase(player.number.begin() + index, player.number.begin() + index + 1);
        player.color.erase(player.color.begin() + index, player.color.begin() + index + 1);
        actionCard();
        SDL_RenderClear(graphics.renderer);
    }
}

#endif // EFFECT_H_INCLUDED
