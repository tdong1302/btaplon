 #ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "defs.h"
using namespace std;

struct Graphics
{
    SDL_Renderer *renderer;
    SDL_Window *window;

    SDL_Texture* goalTexture = nullptr;
    SDL_Texture* playerTexture2=nullptr;
    SDL_Texture* playerTexture1 = nullptr;
    SDL_Texture* ballTexture = nullptr;
    SDL_Texture* fieldTexture = nullptr;

    Mix_Chunk* goalSound = nullptr;
    Mix_Chunk* hitSound=nullptr;


    void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

    SDL_Texture *loadTexture(const char *filename){
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

	return texture;
}
    void init(){

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if (!window) {
            logErrorAndExit("CreateWindow ", SDL_GetError());
        }

        // Khởi tạo renderer từ window
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            logErrorAndExit("CreateRenderer", SDL_GetError());
        }
         goalTexture = loadTexture("assets/goal.png");
         playerTexture1= loadTexture("assets/messi.png");
         playerTexture2=loadTexture("assets/ronaldo.png");
         ballTexture=loadTexture("assets/ball.png");
         fieldTexture=loadTexture("assets/field.png");

         if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
           logErrorAndExit("Failed to open audio: ", Mix_GetError());
        }
        goalSound = Mix_LoadWAV("assets/goal.wav");
        if (!goalSound)
        {
            logErrorAndExit("Failed to load goal sound: " , Mix_GetError());
        }
         hitSound = Mix_LoadWAV("assets/hit.wav");
        if (!hitSound)
        {
            logErrorAndExit("Failed to load hit sound: " , Mix_GetError());
        }

        if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                             TTF_GetError());
        }
    }
    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }


    void quit()
    {
        SDL_DestroyTexture(playerTexture2);
        SDL_DestroyTexture(playerTexture1);
        SDL_DestroyTexture(ballTexture);
        SDL_DestroyTexture(fieldTexture);
        SDL_DestroyTexture(goalTexture);

        Mix_FreeChunk(goalSound);
        Mix_FreeChunk(hitSound);

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }


    TTF_Font* loadFont(const char* path, int size)
    {
        TTF_Font* gFont = TTF_OpenFont( path, size );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
        }
    }

    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor)
    {
        SDL_Surface* textSurface = TTF_RenderText_Solid( font, text, textColor );
        if( textSurface == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
        }

        SDL_FreeSurface( textSurface );
        return texture;
    }
    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
};

#endif // GRAPHICS_H_INCLUDED
