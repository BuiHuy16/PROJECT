#ifndef LOOPGAME_H_INCLUDED
#define LOOPGAME_H_INCLUDED
#include "effect.h"
void chooseNumPlayer(Graphics graphics, TTF_Font* font)
{
    SDL_Texture* menu = graphics.loadTexture("numbersPlayersBG.jpg");
    graphics.prepareScene(menu);

    SDL_Texture* vs1 = graphics.loadTexture("1vs1white.png");
    graphics.DrawScaled(vs1, 480, 190, 200, 95);
    SDL_Texture* vs2 = graphics.loadTexture("1vs2white.png");
    graphics.DrawScaled(vs2, 500, 305, 188, 90);
    SDL_Texture* vs3 = graphics.loadTexture("1vs3white.png");
    graphics.DrawScaled(vs3, 500, 412, 180, 90);

    SDL_Texture* title = graphics.renderText("GAME  MODE", font, whiteColor);
    graphics.renderTexture(title, 450, 100);
    graphics.presentScene();

    SDL_Event event;
    int x, y;
    bool page2=true;
    while (page2) {
        SDL_GetMouseState(&x, &y);
        SDL_PollEvent(&event);
        SDL_Texture* menu2 = graphics.loadTexture("numbersPlayersBG.jpg");
        graphics.prepareScene(menu2);
        SDL_Texture* vs1;
        SDL_Texture* vs2;
        SDL_Texture* vs3;
        SDL_Texture* title = graphics.renderText("GAME  MODE", font, whiteColor);
        graphics.renderTexture(title, 450, 100);

        if(x>507 && x<657 && y>192 && y<271) {
                vs1 = graphics.loadTexture("1vs1green.png");
                graphics.DrawScaled(vs1, 500, 192, 176, 95);
                 }
        else {
            vs1 = graphics.loadTexture("1vs1white.png");
            graphics.DrawScaled(vs1, 480, 190, 200, 95);

        }
        if(x>507 && x<657 && y>302 && y<379) {
                vs2 = graphics.loadTexture("1vs2green.png");
                graphics.DrawScaled(vs2, 501, 306, 179, 91);
            }
        else  {
            vs2 = graphics.loadTexture("1vs2white.png");
            graphics.DrawScaled(vs2, 500, 305, 188, 90);
        }
        if(x>507 && x<657 && y>408 && y<481) {
                vs3 = graphics.loadTexture("1vs3green.png");
                graphics.DrawScaled(vs3, 504, 412, 177, 91);
            }
        else  {
            vs3 = graphics.loadTexture("1vs3white.png");
            graphics.DrawScaled(vs3, 500, 412, 180, 90);

        }
        graphics.presentScene();
        SDL_Delay(0);
        SDL_RenderClear(graphics.renderer);
        SDL_DestroyTexture(menu2);
        SDL_DestroyTexture(vs1);
        vs1 = NULL;
        SDL_DestroyTexture(vs2);
        vs2 = NULL;
        SDL_DestroyTexture(vs3);
        vs3 = NULL;
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONDOWN:
                 cerr << "Down at (" << x << ", " << y << ")\n";
                 break;
            case SDL_MOUSEBUTTONUP:
                 cerr << "Up at (" << x << ", " << y << ")\n";
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
                 break;
        }
    }
}
void startGame(Graphics graphics)
{
    card player1, player2, player3, player4;
    for(int i=0;i<7;i++) drawCard(player1);
    for(int i=0;i<7;i++) drawCard(player2);
    drawCard(player3);
    drawCard(player4);
    if(numberOfPlayers>=3) for(int i=1;i<7;i++) drawCard(player3);
    if(numberOfPlayers>=4) for(int i=1;i<7;i++) drawCard(player4);
    drawCard(pile);
    if(pile.color[0]=="Wild") pile.color[0] = colors[rand() % 4];
    rendergame(graphics, player1, player2, player3, player4);
    renderYourCard(graphics, -1, player1);
    graphics.presentScene();
    while(player1.number.size() !=0 && player2.number.size() !=0 && player3.number.size() !=0 && player4.number.size() !=0) { //gameloop
        switch (abs(playerTurn) % numberOfPlayers + 1) {
            case 1:
                yourMatch(graphics, player1);
                rendergame(graphics, player1, player2, player3, player4);
                renderYourCard(graphics, -1, player1);
                graphics.presentScene();
                //playerDanhBai(player1, pile, numberOfPlayers);
                break;
            case 2:
                aiMatch(graphics, player2);
                rendergame(graphics, player1, player2, player3, player4);
                renderYourCard(graphics, -1, player1);
                graphics.presentScene();
                //ai(player2, pile, numberOfPlayers);
                break;
            case 3:
                aiMatch(graphics, player3);
                rendergame(graphics, player1, player2, player3, player4);
                renderYourCard(graphics, -1, player1);
                graphics.presentScene();
                //ai(player3, pile, numberOfPlayers);
                break;
            case 4:
                aiMatch(graphics, player4);
                rendergame(graphics, player1, player2, player3, player4);
                renderYourCard(graphics, -1, player1);
                graphics.presentScene();
                //ai(player4, pile, numberOfPlayers);
                break;
        }
        SDL_Delay(800);
    }
}

#endif // LOOPGAME_H_INCLUDED
