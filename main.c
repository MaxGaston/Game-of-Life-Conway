#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SDL.h>
#include "gol.h"

int main(int argc, char *argv[])
{
    SDL_Window * window = NULL;
    SDL_Renderer * renderer = NULL;

    int done = 0;
    int paused = 0;
    int board[WIDTH][HEIGHT] = {0};
    int record[WIDTH][HEIGHT] = {0};

    srand(time(NULL));
    
    if(!init_gol(board, START_ALIVE))
    {
        printf("Failed to initialize board!");
        return 1;
    }

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf( "SDL not initialized. SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
        
    //Create window
    window = SDL_CreateWindow("ETEC2110 Lab7", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if(!window)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        printf("Failed to create renderer! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_SetRenderDrawColor(renderer, BLACK);
    SDL_RenderClear(renderer);
    
    SDL_Event event;
    while(!done)
    {
        SDL_PumpEvents();
        
        if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            setCell(board, record, event.button.x, event.button.y, 1);
        }
        else if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
        {
            setCell(board, record, event.button.x, event.button.y, 0);
        }
        
        SDL_PollEvent( &event );

        if(!paused)
        {
            updateRecord(board, record);
            nextGen(board);
        }

        display(board, record, renderer);

        switch( event.type )
        {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            // Pause/Resume
            case SDLK_p:
                paused = !paused;
                break;
            // Reset
            case SDLK_r:
                reset(board, 10000);
                break;
            // Add cells
            case SDLK_a:
                addCells(board, 100);
                break;
            // Kill cells
            case SDLK_k:
                killCells(board, 10);
                break;
            // Step
            case SDLK_SPACE:
                if(paused) nextGen(board);
                break;
            // Quit
            case SDLK_ESCAPE:
                done = 1;
                break;
            }
            break;
        case SDL_QUIT:
            done = 1;
            break;
        default:
            break;
        }
    }

    //Destroy window
    SDL_DestroyWindow(window);
    //Quit SDL subsystems
    SDL_Quit();
	
	return 0;
}