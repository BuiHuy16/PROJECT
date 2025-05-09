#include <SDL_ttf.h>


#include "loopGame.h"
int main(int argc, char *argv[])
{
    init();
    TTF_Font* font = loadFont("assests/fonts/arcadeclassic.ttf", 48);
    TTF_Font* font2 = loadFont("assests/fonts/arcadeclassic.ttf", 60);
    bool running = true;
    srand(time(0));
    string text;
    Mix_Music *song = loadMusic("assests/mixers/mainsong.mp3");
    Mix_Music *song1 = loadMusic("assests/mixers/music1.mp3");
    Mix_Music *song2 = loadMusic("assests/mixers/music2.mp3");
    Mix_Music *song3 = loadMusic("assests/mixers/music3.mp3");
    int randomSong;
    Mix_Chunk *clickk = loadSound("assests/mixers/clickbutton.wav");
    while (running) {
        playMusic(song);
        menugame(font, text);
        playChunk(clickk);
        SDL_RenderClear(renderer);
        if(text == "quit") {
            running = false;
            break;
        }
        chooseNumPlayer(font2);
        playChunk(clickk);
        SDL_RenderClear(renderer);
        Mix_HaltMusic();
        randomSong = rand() % 3 + 1;
        if(randomSong==1) playMusic(song1);
        else if(randomSong==2) playMusic(song2);
        else if(randomSong==3) playMusic(song3);
        getNameOfPlayer();
        startGame();

        SDL_RenderClear(renderer);
        if(backToMenu) {
            backToMenu = false;
            resetFeature();
            continue;
        }
        renderResult(font, font2);
        resetFeature();
        SDL_RenderClear(renderer);
    }
    if (song != nullptr) Mix_FreeMusic( song );
    if (song1 != nullptr) Mix_FreeMusic( song1 );
    if (song2 != nullptr) Mix_FreeMusic( song2 );
    if (song3 != nullptr) Mix_FreeMusic( song3 );
    if(clickk != nullptr) Mix_FreeChunk(clickk);
    TTF_CloseFont(font);
    TTF_CloseFont(font2);
    TTF_CloseFont(fontNum);
    TTF_CloseFont(fontTitle);
    TTF_CloseFont(fontCum1);
    TTF_CloseFont(fontCum2);
    TTF_CloseFont(bigFont);
    SDL_DestroyTexture(menu1);
    SDL_DestroyTexture(menu2);
    SDL_DestroyTexture(playText);
    SDL_DestroyTexture(quitText);
    SDL_DestroyTexture(vs1green);
    SDL_DestroyTexture(vs1white);
    SDL_DestroyTexture(vs2green);
    SDL_DestroyTexture(vs2white);
    SDL_DestroyTexture(vs3green);
    SDL_DestroyTexture(vs3white);
    SDL_DestroyTexture(tickImg);
    SDL_DestroyTexture(avatar);
    SDL_DestroyTexture(emptySquare);
    SDL_DestroyTexture(whiteFrame);
    SDL_DestroyTexture(arrow);
    SDL_DestroyTexture(nope);
    SDL_DestroyTexture(secretCards);
    SDL_DestroyTexture(secretCard);
    SDL_DestroyTexture(endGame);
    SDL_DestroyTexture(mui1);
    SDL_DestroyTexture(mui2);
    SDL_DestroyTexture(mui3);
    SDL_DestroyTexture(mui4);
    SDL_DestroyTexture(nope);
    SDL_DestroyTexture(pauseButton);
    SDL_DestroyTexture(resume);
    SDL_DestroyTexture(returnMenu);
    SDL_DestroyTexture(pausedText);
    quitSDL();
    return 0;
}
