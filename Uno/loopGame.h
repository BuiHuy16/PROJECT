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
    SDL_Texture* title = renderText("GAME  MODE", font, whiteColor);
    SDL_Texture* act1 = renderText("stacking", fontCum2, whiteColor);
    SDL_Texture* act2 = renderText("force  play", fontCum2, whiteColor);
    SDL_Texture* act3 = renderText("draw  to  match", fontCum2, whiteColor);
    SDL_Texture* act4 = renderText("0  and  7", fontCum2, whiteColor);
    SDL_Event event;
    int x, y;
    bool page2=true;
    while (page2) {
        SDL_GetMouseState(&x, &y);
        SDL_PollEvent(&event);
        prepareScene(menu2);
        renderTexture(title, 450, 100);
        DrawScaled(emptySquare, 800, 200, 40, 40);
        renderTexture(act1, 850, 200);
        DrawScaled(emptySquare, 800, 275, 40, 40);
        renderTexture(act2, 850, 275);
        DrawScaled(emptySquare, 800, 350, 40, 40);
        renderTexture(act3, 850, 350);
        DrawScaled(emptySquare, 800, 425, 40, 40);
        renderTexture(act4, 850, 425);
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
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT) {
                 //   cout<<x<<" "<<y<<endl;
                    if(x>806 && x<839 && y>205 && y<237) {
                        if(!isStacked) isStacked = true;
                        else isStacked = false;
                    }
                    if(x>806 && x<839 && y>280 && y<312) {
                        if(!forcePLay) forcePLay = true;
                        else forcePLay = false;
                    }
                    if(x>806 && x<839 && y>355 && y<387) {
                        if(!drawToMatch) drawToMatch = true;
                        else drawToMatch = false;
                    }
                    if(x>806 && x<839 && y>430 && y<462) {
                        if(!zeroSevenRule) zeroSevenRule = true;
                        else zeroSevenRule = false;
                    }
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
        if(isStacked) DrawScaled(tickImg, 800, 190, 50, 50);
        if(forcePLay) DrawScaled(tickImg, 800, 265, 50, 50);
        if(drawToMatch) DrawScaled(tickImg, 800, 340, 50, 50);
        if(zeroSevenRule) DrawScaled(tickImg, 800, 415, 50, 50);
        presentScene();
    }
    SDL_DestroyTexture(title);
    SDL_DestroyTexture(act1);
    SDL_DestroyTexture(act2);
    SDL_DestroyTexture(act3);
    SDL_DestroyTexture(act4);
}
void startGame()
{
    for(int i=0;i<7;i++) drawCard(player1);
    for(int i=0;i<7;i++) drawCard(player2);
    if(numberOfPlayers>=3) for(int i=0;i<7;i++) drawCard(player3);
    if(numberOfPlayers>=4) for(int i=0;i<7;i++) drawCard(player4);
    pile.number = numbers[rand() % 13];
    pile.color = colors[rand() % 4];
    for(int i=0;i<player1.size();i++) {
        myCard.push_back({ 300+i*dd, 480}); //lay toa do 7 la bai ban dau
    }
    SDL_Event event;
    while(!gameOver()) { //gameloop
        SDL_PollEvent(&event);
        rendergame();
        presentScene();
        Paused(event);
        if(abs(playerTurn) % numberOfPlayers != 0 || isSkip>0) {
          //  tương đương với hàm SDL_Delay()
            for(int i=0;i<delayTime;i++) {
                SDL_PollEvent(&event);
                SDL_RenderClear(renderer);
                rendergame();
                presentScene();
                Paused(event);
                if(backToMenu) break;
            }
        }
        if(isSkip>0) {
            isSkip = 2;
            SDL_RenderClear(renderer);
            rendergame();
            presentScene();
            playChunk(skipWav);
            for(int i=0;i<delayTime;i++) {
                SDL_PollEvent(&event);
                SDL_RenderClear(renderer);
                rendergame();
                presentScene();
                Paused(event);
                if(backToMenu) break;
            }
            isSkip = 0;
            nextturn();
            continue;
        }
        if(backToMenu) break;
        switch (abs(playerTurn) % numberOfPlayers + 1) {
            case 1:
                yourMatch(event);
                break;
            case 2:
                aiMatch(player2, 166, 260, event);
                break;
            case 3:
                aiMatch(player3, 616, 40, event);
                break;
            case 4:
                aiMatch(player4, 966.8, 260, event);
                break;
        }
        if(backToMenu) break;
        renderCard();
        SDL_RenderClear(renderer);
    }
    Mix_HaltMusic();
    cumlativeCards = 0;
    if(!backToMenu) {
       for(int i=0;i<=delayTime;i++) {
        SDL_PollEvent(&event);
        rendergame();
        presentScene();
        }
    }
}

#endif // LOOPGAME_H_INCLUDED
