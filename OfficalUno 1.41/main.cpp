#include <SDL_ttf.h>


#include "loopGame.h"
using namespace std;

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();
    //hiện menuBG
    SDL_Texture* menu = graphics.loadTexture("menuBG.jpg");
    graphics.prepareScene(menu);
    TTF_Font* font = graphics.loadFont("arcadeclassic.ttf", 48);
    TTF_Font* font2 = graphics.loadFont("arcadeclassic.ttf", 60);
    SDL_Texture* playText = graphics.renderText("PLAY", font, whiteColor);
    graphics.renderTexture(playText, 537, 450);
    SDL_Texture* quitText = graphics.renderText("QUIT", font, whiteColor);
    graphics.renderTexture(quitText, 537, 510);
    graphics.presentScene();
    bool endGame = false;
    srand(time(0));
    SDL_Event event;
    int x, y;
    bool page1 = true;
    while (page1) {

        SDL_GetMouseState(&x, &y);
        SDL_PollEvent(&event);
        if(x>537 && x<628 && y>450 && y<483) {
                    playText = graphics.renderText("PLAY", font, blackColor);
                    graphics.renderTexture(playText, 537, 450);
                 }
        else {
            playText = graphics.renderText("PLAY", font, whiteColor);
                    graphics.renderTexture(playText, 537, 450);
        }
        if(x>537 && x<628 && y>510 && y<543) {
                    quitText = graphics.renderText("QUIT", font, blackColor);
                    graphics.renderTexture(quitText, 537, 510);
                 }
        else {
            quitText = graphics.renderText("QUIT", font, whiteColor);
                    graphics.renderTexture(quitText, 537, 510);
        }
        graphics.presentScene();
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONDOWN:
                 cerr << "Down at (" << x << ", " << y << ")\n";

                 break;
            case SDL_MOUSEBUTTONUP:
                 cerr << "Up at (" << x << ", " << y << ")\n";
                 if(x>537 && x<628 && y>450 && y<483) {
                    SDL_Delay(60);
                    SDL_RenderClear(graphics.renderer);
                    chooseNumPlayer(graphics, font2);
                    SDL_RenderClear(graphics.renderer);
                    startGame(graphics);
                    page1 = false;
                 }
                 else {
                    playText = graphics.renderText("PLAY", font, whiteColor);
                    graphics.renderTexture(playText, 537, 450);
                 }
                 if(x>537 && x<628 && y>510 && y<543) {
                    SDL_Delay(60);
                    endGame = true;
                    page1 = false;
                 }
                 else {
                    playText = graphics.renderText("PLAY", font, whiteColor);
                    graphics.renderTexture(playText, 537, 450);
                 }
                 break;
                 graphics.presentScene();
        }

    }
    if(endGame) {
        graphics.quit();
      return 0;
    }

    graphics.quit();
    return 0;
}
