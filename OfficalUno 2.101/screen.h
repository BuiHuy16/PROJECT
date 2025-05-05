#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED
#include "khaiquat.h"
#include "special.h"
void Paused(SDL_Event &event)
{
    int x0, y0;
    SDL_GetMouseState(&x0, &y0);
    if((event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT)
       || (event.type == SDL_KEYDOWN ) ) {
            if((x0>=1152 && x0<=1187 && y0>=1 && y0<=36) || event.key.keysym.sym == SDLK_ESCAPE) {
                bool isPaused = true;
                int x, y;
                double xx = 104.9;
                double yy = 161.6;
                int aa = 11 % 12;
                int bb = 11 / 12;
                SDL_Rect srcRect = { xx*aa, yy*bb, xx, yy};
                SDL_Rect dstRect1 = { 350, 250, 90, 139 };
                SDL_Rect dstRect2 = { 750, 250, 90, 139 };
                SDL_Rect screen = {200, 100, 800, 450};
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderFillRect(renderer, &screen);
                renderTexture(pausedText, 510, 150);
                SDL_RenderCopy(renderer, secretCards, &srcRect, &dstRect1);
                SDL_RenderCopy(renderer, secretCards, &srcRect, &dstRect2);
                DrawScaled(resume, 370, 297, 50, 50);
                DrawScaled(returnMenu, 775, 300, 40, 40);
                while(isPaused) {
                    SDL_PollEvent(&event);

                    presentScene();
                    switch (event.type) {
                        case SDL_QUIT:
                             exit(0);
                             break;
                        case SDL_MOUSEBUTTONUP:
                             if(event.button.button == SDL_BUTTON_LEFT) {
                                SDL_GetMouseState(&x, &y);
                                if(x>=350 && x<=440 && y>=300 && y<=439) {
                                    isPaused = false;
                                }
                                if(x>=750 && x<=840 && y>=300 && y<=439) {
                                    isPaused = false;
                                    backToMenu = true;
                                }

                             }
                             break;
                    }
                }
            }
    }
}
void chooseColourScreen()
{
    SDL_Rect screen = {300, 150, 600, 350};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0 );
    SDL_RenderFillRect(renderer, &screen);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &screen);

    renderTexture(cycText, 425, 175);
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
}
void renderResult(TTF_Font* font1, TTF_Font* font2)
{
    prepareScene(endGame);
    string res;
    if(player1.size() == 0) res = "YOU  WON!";
    else res = "YOU  LOST!";
    SDL_Texture* resultText = renderText(res, font2, whiteColor);
    renderTexture(resultText, 500, 100);
    SDL_Texture* key = renderText("Press any key to continue", font1, whiteColor);
    renderTexture(key, 380, 400);
    presentScene();
    waitUntilKeyPressed();
    SDL_DestroyTexture(resultText);
    SDL_DestroyTexture(key);
}

#endif // SCREEN_H_INCLUDED
