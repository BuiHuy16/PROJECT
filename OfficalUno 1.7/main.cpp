#include <SDL_ttf.h>


#include "loopGame.h"
int main(int argc, char *argv[])
{
    init();
    TTF_Font* font = loadFont("arcadeclassic.ttf", 48);
    TTF_Font* font2 = loadFont("arcadeclassic.ttf", 60);
    bool running = true;
    srand(time(0));
    string text;
    //Mix_Music *song = graphics.loadMusic("mainsong.mp3");
    //graphics.play(song);
    while (running) {
        menugame(font, text);
        SDL_RenderClear(renderer);
        SDL_Delay(60);
        if(text == "quit") {
            running = false;
            break;
        }
        chooseNumPlayer(font2);
        SDL_RenderClear(renderer);
        startGame();
        SDL_RenderClear(renderer);
        renderResult(font, font2);
        SDL_RenderClear(renderer);
        resetFeature();
    }
    TTF_CloseFont(font);
    TTF_CloseFont(font2);
    SDL_DestroyTexture(menu1);
    SDL_DestroyTexture(menu2);
    SDL_DestroyTexture(playText);
    SDL_DestroyTexture(quitText);
    quitSDL();
    return 0;
}
