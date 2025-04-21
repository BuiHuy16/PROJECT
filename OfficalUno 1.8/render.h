#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "feature.h"
void rendermenu(TTF_Font* font, string inf)
{
    prepareScene(menu1);
    if(inf == "blackPlay") {
        playText = renderText("PLAY", font, blackColor);
        renderTexture(playText, 537, 450);
    }
    else  {
        playText = renderText("PLAY", font, whiteColor);
        renderTexture(playText, 537, 450);
    }
    if(inf == "blackQuit") {
        quitText = renderText("QUIT", font, blackColor);
        renderTexture(quitText, 537, 510);
    }
    else  {
        quitText = renderText("QUIT", font, whiteColor);
        renderTexture(quitText, 537, 510);
    }

    presentScene();
}

void rendergame()
{
    if(pile.color=="green") fillColor( 0, 255, 0, 255);
    else if(pile.color=="blue") fillColor( 100, 100, 255, 255);
    else if(pile.color=="red") fillColor( 255, 0, 0, 255);
    else if(pile.color=="yellow") fillColor( 255, 255, 0, 255);
    bool fillFrame = false;
    TTF_Font* fontNum = loadFont("arcadeclassic.ttf", 30);
    DrawScaled(avatar, 175, 496, 100, 100);
    if(abs(playerTurn) % numberOfPlayers==0) {
        SDL_SetTextureColorMod(whiteFrame, 255, 165, 0);
        fillFrame = true;
    }
    else SDL_SetTextureColorMod(whiteFrame, 255, 255, 255);
    DrawScaled(whiteFrame, 160, 471, 136, 136);

	SDL_Rect rect[4];
    rect[0].x=209;
    rect[0].y=456;
    rect[0].h=30;
    rect[0].w=30;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0 );
    SDL_RenderFillRect(renderer, &rect[0]);
    string numP1 = to_string(player1.size());
    SDL_Texture* numberCardP1 = renderText(numP1, fontNum, blackColor);
    renderTexture(numberCardP1, 215, 456);


    DrawScaled(avatar, 50, 275, 100, 100);

	if(abs(playerTurn) % numberOfPlayers==1) {
        SDL_SetTextureColorMod(whiteFrame, 255, 165, 0);
        fillFrame = true;
    }
    else if(fillFrame) {
        SDL_SetTextureColorMod(whiteFrame, 255, 255, 255);
        fillFrame = false;
    }

    DrawScaled(whiteFrame, 35, 250, 136, 136);

    DrawScaled(secretCards, 166, 274, 67.2, 104.4);
    rect[1].x=67;
    rect[1].y=235;
    rect[1].h=30;
    rect[1].w=30;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0 );
    SDL_RenderFillRect(renderer, &rect[1]);
    string numP2 = to_string(player2.size());
    SDL_Texture* numberCardP2 = renderText(numP2, fontNum, blackColor);
    renderTexture(numberCardP2, 73, 235);

    if(numberOfPlayers>2) {

        DrawScaled(avatar, 500, 50, 100, 100);

        if(abs(playerTurn) % numberOfPlayers==2) {
            SDL_SetTextureColorMod(whiteFrame, 255, 165, 0);
            fillFrame = true;
        }
        else if(fillFrame) {
            SDL_SetTextureColorMod(whiteFrame, 255, 255, 255);
            fillFrame = false;
        }
        DrawScaled(whiteFrame, 485, 25, 136, 136);

        DrawScaled(secretCards, 616, 49, 67.2, 104.4);
        rect[2].x=534;
        rect[2].y=10;
        rect[2].h=30;
        rect[2].w=30;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0 );
        SDL_RenderFillRect(renderer, &rect[2]);
        string numP3 = to_string(player3.size());
        SDL_Texture* numberCardP3 = renderText(numP3, fontNum, blackColor);
        renderTexture(numberCardP3, 540, 10);
    }
    if(numberOfPlayers>3) {

        DrawScaled(avatar, 1050, 275, 100, 100);

        if(abs(playerTurn) % numberOfPlayers==3) {
            SDL_SetTextureColorMod(whiteFrame, 255, 165, 0);
            fillFrame = true;
        }
        else if(fillFrame) {
            SDL_SetTextureColorMod(whiteFrame, 255, 255, 255);
            fillFrame = false;
        }
        DrawScaled(whiteFrame, 1035, 250, 136, 136);

        DrawScaled(secretCards, 966.8, 274, 67.2, 104.4);
        rect[3].x=1103;
        rect[3].y=235;
        rect[3].h=30;
        rect[3].w=30;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0 );
        SDL_RenderFillRect(renderer, &rect[3]);
        string numP4 = to_string(player4.size());
        SDL_Texture* numberCardP4 = renderText(numP4, fontNum, blackColor);
        renderTexture(numberCardP4, 1111, 235);
    }
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0 );
    DrawFilledCircle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 150);

    DrawScaled(secretCards, 500, 260, 90, 139);
    if(isSkip==2) {
        switch (abs(playerTurn) % numberOfPlayers + 1) {
            case 1:
                DrawScaled(nope, 175, 496, 100, 100);
                break;
            case 2:
                DrawScaled(nope, 50, 275, 100, 100);
                break;
            case 3:
                DrawScaled(nope, 500, 50, 100, 100);
                break;
            case 4:
                DrawScaled(nope, 1050, 275, 100, 100);
                break;
        }
    }

    if(direct) {
        DrawScaled(mui1, 700, 200, 300, 300);
        DrawScaled(mui2, 260, 190, 260, 260);
    }
    else {
        DrawScaled(mui4, 700, 200, 260, 260);
        DrawScaled(mui3, 260, 200, 275, 275);
    }

    TTF_CloseFont(fontNum);
    for(int i=0;i<4;i++) rect[i] = {0, 0, 0, 0};
}

#endif // GAME_H_INCLUDED
