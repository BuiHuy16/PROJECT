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
    if(pile.color == "wild") {
        pile.color = tmpColor;
        if(pile.color=="green") fillColor( 0, 255, 0, 255);
        else if(pile.color=="blue") fillColor( 100, 100, 255, 255);
        else if(pile.color=="red") fillColor( 255, 0, 0, 255);
        else if(pile.color=="yellow") fillColor( 255, 255, 0, 255);
    }
    else if(pile.color=="green") fillColor( 0, 255, 0, 255);
    else if(pile.color=="blue") fillColor( 100, 100, 255, 255);
    else if(pile.color=="red") fillColor( 255, 0, 0, 255);
    else if(pile.color=="yellow") fillColor( 255, 255, 0, 255);
    bool fillFrame = false;

    DrawScaled(avatar, 175, 496, 100, 100);
    if(abs(playerTurn) % numberOfPlayers==0) {
        SDL_SetTextureColorMod(whiteFrame, 255, 165, 0);
        fillFrame = true;
    }
    else SDL_SetTextureColorMod(whiteFrame, 255, 255, 255);
    DrawScaled(whiteFrame, 160, 471, 136, 136);

	SDL_Rect rect[4];
    rect[0].x=209;
    rect[0].y=452;
    rect[0].h=35;
    rect[0].w=35;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0 );
    SDL_RenderFillRect(renderer, &rect[0]);
    string numP1 = to_string(player1.size());
    SDL_Texture* numberCardP1 = renderText(numP1, fontNum, blackColor);
    if(player1.size()>=10) renderTexture(numberCardP1, 210, 453);
    else renderTexture(numberCardP1, 218, 453);


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
   if(!aiWin[0]) getSecretCard(161, 272, 70, 103);
    rect[1].x=67;
    rect[1].y=232;
    rect[1].h=35;
    rect[1].w=35;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0 );
    SDL_RenderFillRect(renderer, &rect[1]);
    string numP2 = to_string(player2.size());
    SDL_Texture* numberCardP2 = renderText(numP2, fontNum, blackColor);
    if(player2.size()>=10) renderTexture(numberCardP2, 68, 232);
    else renderTexture(numberCardP2, 76, 232);

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
        if(!aiWin[1]) getSecretCard(611, 47, 70, 103);
        rect[2].x=534;
        rect[2].y=7;
        rect[2].h=35;
        rect[2].w=35;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0 );
        SDL_RenderFillRect(renderer, &rect[2]);
        string numP3 = to_string(player3.size());
        SDL_Texture* numberCardP3 = renderText(numP3, fontNum, blackColor);
        if(player3.size()>=10) renderTexture(numberCardP3, 535, 7);
        else renderTexture(numberCardP3, 543, 7);
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
        if(!aiWin[2]) getSecretCard(961.8, 272, 70, 103);
        rect[3].x=1103;
        rect[3].y=232;
        rect[3].h=35;
        rect[3].w=35;
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0 );
        SDL_RenderFillRect(renderer, &rect[3]);
        string numP4 = to_string(player4.size());
        SDL_Texture* numberCardP4 = renderText(numP4, fontNum, blackColor);
        if(player4.size()>=10) renderTexture(numberCardP4, 1106, 232);
        else renderTexture(numberCardP4, 1114, 232);
    }
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0 );
    DrawFilledCircle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 150);

    getSecretCard(495, 258, 100, 147); // ve desk
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

    if(cumlativeCards!=0 && showCumText) {
        string cumText1 = "+";
        string cumText2 = to_string(cumlativeCards);
        SDL_Texture* numOfCum1 = renderText(cumText1, fontCum1, blackColor);
        SDL_Texture* numOfCum2 = renderText(cumText2, fontCum2, blackColor);
        renderTexture(numOfCum1, 520, 210);
        renderTexture(numOfCum2, 550, 215);
    }

    getCard(pile.number, pile.color, 615, 260);
    for(int i=0;i<myCard.size();i++) {
        getCard(player1[i].number, player1[i].color, myCard[i].x, myCard[i].y);
    }
    DrawScaled(pauseButton, 1150, 0, 50, 50);
    for(int i=0;i<4;i++) rect[i] = {0, 0, 0, 0};
}

void renderArrow()
{
    if(arrowY==210) arrowDown = false;
    else if(arrowY==205) arrowDown = true;
    if(arrowDown) arrowY += 0.25;
    else arrowY-=0.25;
    DrawScaled(arrow, 525, arrowY, 40, 40);
}

#endif // GAME_H_INCLUDED
