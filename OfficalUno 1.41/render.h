#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "feature.h"
void renderYourCard(Graphics graphics, int index, card &player1)
{
    for(int i=0;i<player1.number.size();i++) {
        if(i==index) continue;
        getCard(graphics, player1.number[i], player1.color[i], 300+i*60, 480);
    }
}
void rendergame(Graphics graphics, card player1, card player2, card player3, card player4)
{
    if(pile.color[0]=="green") graphics.fillColor( 0, 255, 0, 255);
    else if(pile.color[0]=="blue") graphics.fillColor( 100, 100, 255, 255);
    else if(pile.color[0]=="red") graphics.fillColor( 255, 0, 0, 255);
    else if(pile.color[0]=="yellow") graphics.fillColor( 255, 255, 0, 255);
    TTF_Font* font = graphics.loadFont("arcadeclassic.ttf", 30);

    SDL_Texture* avatar = graphics.loadTexture("unknown.jfif");
    graphics.DrawScaled(avatar, 175, 496, 100, 100);
	SDL_Texture* whiteFrame = graphics.loadTexture("nentrang.png");
    graphics.DrawScaled(whiteFrame, 160, 471, 136, 136);
	SDL_Rect rect[4];
    rect[0].x=209;
    rect[0].y=456;
    rect[0].h=30;
    rect[0].w=30;
    SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 0 );
    SDL_RenderFillRect(graphics.renderer, &rect[0]);
    char* numP1 = new char[3];
    if(player1.number.size()<10) {
        numP1[0] = (char) (player1.number.size() + 48);
        numP1[1] = '\0';
    }
    else {
        numP1[0] = (char) (player1.number.size() / 10 + 48);
        numP1[1] = (char) (player1.number.size() % 10 + 48);
        numP1[2] = '\0';
    }
    SDL_Texture* numberCardP1 = graphics.renderText(numP1, font, blackColor);
    graphics.renderTexture(numberCardP1, 215, 456);

    avatar = graphics.loadTexture("unknown.jfif");
    graphics.DrawScaled(avatar, 50, 275, 100, 100);
	whiteFrame = graphics.loadTexture("nentrang.png");
    graphics.DrawScaled(whiteFrame, 35, 250, 136, 136);
	SDL_Texture* secretCards = graphics.loadTexture("Cards/secretcard.png");
    graphics.DrawScaled(secretCards, 166, 274, 67.2, 104.4);
    rect[1].x=67;
    rect[1].y=235;
    rect[1].h=30;
    rect[1].w=30;
    SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 0 );
    SDL_RenderFillRect(graphics.renderer, &rect[1]);
    char* numP2 = new char[3];
    if(player2.number.size()<10) {
        numP2[0] = (char) (player2.number.size() + 48);
        numP2[1] = '\0';
    }
    else {
        numP2[0] = (char) (player2.number.size() / 10 + 48);
        numP2[1] = (char) (player2.number.size() % 10 + 48);
        numP2[2] = '\0';
    }
    SDL_Texture* numberCardP2 = graphics.renderText(numP2, font, blackColor);
    graphics.renderTexture(numberCardP2, 73, 235);
    delete[] numP1;
    delete[] numP2;
    if(numberOfPlayers>2) {
        avatar = graphics.loadTexture("unknown.jfif");
        graphics.DrawScaled(avatar, 500, 50, 100, 100);
        whiteFrame = graphics.loadTexture("nentrang.png");
        graphics.DrawScaled(whiteFrame, 485, 25, 136, 136);
        secretCards = graphics.loadTexture("Cards/secretcard.png");
        graphics.DrawScaled(secretCards, 616, 49, 67.2, 104.4);
        rect[2].x=534;
        rect[2].y=10;
        rect[2].h=30;
        rect[2].w=30;
        SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 0 );
        SDL_RenderFillRect(graphics.renderer, &rect[2]);
        char* numP3 = new char[3];
        if(player3.number.size()<10) {
            numP3[0] = (char) (player3.number.size() + 48);
            numP3[1] = '\0';
        }
        else {
            numP3[0] = (char) (player3.number.size() / 10 + 48);
            numP3[1] = (char) (player3.number.size() % 10 + 48);
            numP3[2] = '\0';
        }
        SDL_Texture* numberCardP3 = graphics.renderText(numP3, font, blackColor);
        graphics.renderTexture(numberCardP3, 540, 10);
        delete[] numP3;
    }
    if(numberOfPlayers>3) {
        avatar = graphics.loadTexture("unknown.jfif");
        graphics.DrawScaled(avatar, 1050, 275, 100, 100);
        whiteFrame = graphics.loadTexture("nentrang.png");
        graphics.DrawScaled(whiteFrame, 1035, 250, 136, 136);
        secretCards = graphics.loadTexture("Cards/secretcard.png");
        graphics.DrawScaled(secretCards, 966.8, 274, 67.2, 104.4);
        rect[3].x=1103;
        rect[3].y=235;
        rect[3].h=30;
        rect[3].w=30;
        SDL_SetRenderDrawColor(graphics.renderer, 255, 255, 255, 0 );
        SDL_RenderFillRect(graphics.renderer, &rect[3]);
        char* numP4 = new char[3];
        if(player4.number.size()<10) {
            numP4[0] = (char) (player4.number.size() + 48);
            numP4[1] = '\0';
        }
        else {
            numP4[0] = (char) (player4.number.size() / 10 + 48);
            numP4[1] = (char) (player4.number.size() % 10 + 48);
            numP4[2] = '\0';
        }
        SDL_Texture* numberCardP4 = graphics.renderText(numP4, font, blackColor);
        graphics.renderTexture(numberCardP4, 1111, 235);
        delete[] numP4;
    }
    SDL_SetRenderDrawColor(graphics.renderer, 200, 200, 200, 0 );
    graphics.DrawFilledCircle(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 150);
    SDL_Texture* randomCard = graphics.loadTexture("Cards/secretcard.png");
    graphics.DrawScaled(randomCard, 500, 260, 90, 139);
    getCard(graphics, pile.number[0], pile.color[0], 615, 260);
}


#endif // GAME_H_INCLUDED
