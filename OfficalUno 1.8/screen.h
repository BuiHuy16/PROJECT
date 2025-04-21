#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED
#include "khaiquat.h"
string chooseYourColour()
{
    SDL_Rect screen = {300, 150, 600, 350};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0 );
    SDL_RenderFillRect(renderer, &screen);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &screen);
    TTF_Font* font = loadFont("arcadeclassic.ttf", 40);
    SDL_Texture* text = renderText("Choose your colour", font, blackColor);
    renderTexture(text, 425, 175);
    screen.x = 500;
    screen.y = 225;
    screen.w = 100;
    screen.h = 100;
    SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255);
    SDL_RenderFillRect(renderer, &screen);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &screen);
    screen.x = 600;
    screen.y = 225;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &screen);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &screen);
    screen.x = 500;
    screen.y = 325;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &screen);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &screen);
    screen.x = 600;
    screen.y = 325;
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &screen);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &screen);
    presentScene();
    SDL_RenderClear(renderer);
    TTF_CloseFont(font);
    screen = {0, 0, 0, 0};
    SDL_DestroyTexture(text);
    SDL_Event event;
    int x, y;
    while (true) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT) {
                    SDL_GetMouseState(&x, &y);
                 if(x>=500 && x<=600) {
                    if(y>=225 && y<=325) return "blue";
                    else if(y>=325 && y<=425) return "red";
                 }
                 else if(x>=600 && x<=700) {
                    if(y>=225 && y<=325) return "green";
                    else if(y>=325 && y<=425) return "yellow";
                 }
                }
                 break;
        }
        //SDL_Delay(50);

    }
}

void renderResult(TTF_Font* font1, TTF_Font* font2)
{
    prepareScene(endGame);
    string res;
    if(player1.size() == 0) res = "YOU  WON!";
    else res = "YOU  LOST!";
    SDL_Texture* resultText = renderText(res, font2, whiteColor);
    renderTexture(resultText, 120, 100);
    SDL_Texture* key = renderText("Press any key to continue", font1, whiteColor);
    renderTexture(key, 100, 400);
    presentScene();
    waitUntilKeyPressed();
    SDL_DestroyTexture(resultText);
    SDL_DestroyTexture(key);
}

#endif // SCREEN_H_INCLUDED
