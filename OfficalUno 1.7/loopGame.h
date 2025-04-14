#ifndef LOOPGAME_H_INCLUDED
#define LOOPGAME_H_INCLUDED
#include "effect.h"
void menugame(TTF_Font* font, string &text)
{
    SDL_Event event;
    int x, y;
    bool page1 = true;

    while (page1) {
        SDL_GetMouseState(&x, &y);
        SDL_PollEvent(&event);
        if(x>537 && x<628 && y>450 && y<483) { //play is black
                    rendermenu(font, "blackPlay");
                    SDL_RenderClear(renderer);
                 }
        else if(x>537 && x<628 && y>510 && y<543) { // quit is black
                    rendermenu(font, "blackQuit");
                    SDL_RenderClear(renderer);
                 }
        else {  //no black
            rendermenu(font, " ");
            SDL_RenderClear(renderer);
        }
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONUP:
                 if(event.button.button == SDL_BUTTON_LEFT) {
                    if(x>537 && x<628 && y>450 && y<483) {
                    text = "play";
                    page1 = false;
                 }
                     if(x>537 && x<628 && y>510 && y<543) {
                        text = "quit";
                        page1 = false;
                     }
                 }
                 break;
        }

    }
}
void chooseNumPlayer(TTF_Font* font)
{
    prepareScene(menu2);


    DrawScaled(vs1white, 480, 190, 200, 95);

    DrawScaled(vs2white, 500, 305, 188, 90);

    DrawScaled(vs3white, 500, 412, 180, 90);

    SDL_Texture* title = renderText("GAME  MODE", font, whiteColor);
    renderTexture(title, 450, 100);
    presentScene();

    SDL_Event event;
    int x, y;
    bool page2=true;
    while (page2) {
        SDL_GetMouseState(&x, &y);
        SDL_PollEvent(&event);
        if(x>507 && x<657 && y>192 && y<271) {

                DrawScaled(vs1green, 500, 192, 176, 95);
                 }
        else {

            DrawScaled(vs1white, 480, 190, 200, 95);

        }
        if(x>507 && x<657 && y>302 && y<379) {

                DrawScaled(vs2green, 501, 306, 179, 91);
            }
        else  {

            DrawScaled(vs2white, 500, 305, 188, 90);
        }
        if(x>507 && x<657 && y>408 && y<481) {

                DrawScaled(vs3green, 504, 412, 177, 91);
            }
        else  {

            DrawScaled(vs3white, 500, 412, 180, 90);

        }
        presentScene();
        SDL_Delay(0);
        //SDL_RenderClear(graphics.renderer);

        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT) {
                    if(x>507 && x<657 && y>192 && y<271) {
                    numberOfPlayers = 2;
                    page2 = false;
                     }
                     else if(x>507 && x<657 && y>302 && y<379) {
                        numberOfPlayers = 3;
                        page2 = false;
                     }
                     else if(x>507 && x<657 && y>408 && y<481) {
                        numberOfPlayers = 4;
                        page2 = false;
                     }
                }
                 break;
        }
    }
}
void startGame()
{
    for(int i=0;i<7;i++) drawCard(player1);
    for(int i=0;i<7;i++) drawCard(player2);
    drawCard(player3);
    drawCard(player4);
    if(numberOfPlayers>=3) for(int i=1;i<7;i++) drawCard(player3);
    if(numberOfPlayers>=4) for(int i=1;i<7;i++) drawCard(player4);
    pile.number = numbers[rand() % 13];
    pile.color = colors[rand() % 4];
    SDL_Texture* pileImage = getCard(pile.number, pile.color);


    for(int i=0;i<player1.size();i++) {
        SDL_Texture* myHand = getCard(player1[i].number, player1[i].color);
        myCard.push_back({ 300+i*60, 480, myHand});

    }


    while(player1.size() !=0 && player2.size() !=0 && player3.size() !=0 && player4.size() !=0) { //gameloop
        rendergame();
        DrawScaled( pileImage, 615, 260, 90, 139);
        for(int i=0;i<myCard.size();i++) {
            DrawScaled( myCard[i].texture, myCard[i].x, myCard[i].y, 90, 139);
        }
        presentScene();

        if(abs(playerTurn) % numberOfPlayers != 0) {
            SDL_Delay(1000);
        }
        switch (abs(playerTurn) % numberOfPlayers + 1) {
            case 1:
                yourMatch(pileImage);
                break;
            case 2:
                aiMatch(pileImage, player2, 166, 260);
                break;
            case 3:
                aiMatch(pileImage, player3, 616, 40);
                break;
            case 4:
                aiMatch(pileImage, player4, 966.8, 260);
                break;
        }
        pileImage = getCard(pile.number, pile.color);
        SDL_RenderClear(renderer);
    }
    rendergame();
    DrawScaled( pileImage, 615, 260, 90, 139);
    if(myCard.size()!=0) {
        for(int i=0;i<myCard.size();i++) {
            DrawScaled( myCard[i].texture, myCard[i].x, myCard[i].y, 90, 139);
        }
    }
    presentScene();
    SDL_Delay(1000);
}

#endif // LOOPGAME_H_INCLUDED
