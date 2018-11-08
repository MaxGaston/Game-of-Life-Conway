#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "gol.h"

/*
1. A live cell with fewer than two live neighbors dies.
2. A live cell with more than three live neighbors also dies.
3. A live cell with exactly two or three live neighbors lives.
4. A dead cell with exactly three live neighbors becomes alive.
*/

int init_gol(int board[WIDTH][HEIGHT], int num_alive)
{
    if(num_alive > CELLS) return 0;

    addCells(board, num_alive);

    return 1;
}

void display(int board[WIDTH][HEIGHT], int record[WIDTH][HEIGHT], SDL_Renderer * rend)
{
    SDL_SetRenderDrawColor(rend, BLACK);
    SDL_RenderClear(rend);
    
    SDL_Rect rect;
    rect.w = 4;
    rect.h = 4;

    float r, g, b, a;
    g = 0;
    a = 255;
    int border = BORDER >> 1;
    for_x for_y
    {    
        rect.x = x * 5 + border;
        rect.y = y * 5 + border;

        float n = record[x][y];

        r = (BRIGHTNESS_LEVELS / n) * 255;
        b = 255 - r;

        SDL_SetRenderDrawColor(rend, (int)r, (int)g, (int)b, (int)a);
        SDL_RenderFillRect(rend, &rect);  
    }

    SDL_RenderPresent(rend);
}

int neighbors(int board[WIDTH][HEIGHT], int c, int r)
{
    int ret = 0;

    int ymin = r > 0 ? -1 : 0;
    int ymax = r < HEIGHT ? 1 : 0;
    int xmin = c > 0 ? -1 : 0;
    int xmax = c < WIDTH ? 1 : 0;

    for(int x = xmin; x <= xmax; x++)
    {
        for(int y = ymin; y <= ymax; y++)
        {
            ret += board[c+x][r+y];
        }
    }
    
    if(board[c][r]) ret--;

    return ret > 0 ? ret : 0;
}

int nextState(int board[WIDTH][HEIGHT], int c, int r)
{
    int n = neighbors(board, c, r);

    if(board[c][r] && n >= 2 && n <= 3) return 1;
    else if(!board[c][r] && n == 3) return 1;
    else return 0;
}

int nextGen(int board[WIDTH][HEIGHT])
{
    int tmp[WIDTH][HEIGHT] = {0};
    for_x for_y
    {
        tmp[x][y] = nextState(board, x, y);
    }
    memcpy(board, tmp, CELLS * sizeof(int));
}

int addCells(int board[WIDTH][HEIGHT], int num)
{
    if(num > CELLS) return 0;
    int attempt = 0;

    while(num)
    {
        if(attempt++ > ATTEMPT_LIMIT) break;

        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;

        if(board[x][y]) continue;

        board[x][y] = 1;
        num--;
    }

    return 1;
}

int setCell(int board[WIDTH][HEIGHT], int record[WIDTH][HEIGHT], int x, int y, int state)
{
    int cellx =  (x / 5) - 2;
    int celly =  (y / 5) - 2;
    if(cellx >= 0 && cellx <= WIDTH)
        if(celly >= 0 && celly <= HEIGHT)
        {
            board[cellx][celly] = state;
            record[cellx][celly] = state;
        }
}

int reset(int board[WIDTH][HEIGHT], int num)
{
    if(num > CELLS) return 0;

    memset(board, 0, CELLS * sizeof(int));

    addCells(board, num);

    return 1;
}

int killCells(int board[WIDTH][HEIGHT], int chance)
{
    for_x for_y
    {
        if(board[x][y] == 1)
        {
            int tmp = rand() % 100;
            if(tmp <= chance) board[x][y] = 0;
        }
    }
}

void updateRecord(int board[WIDTH][HEIGHT], int record[WIDTH][HEIGHT])
{
    for_x for_y
    {
        if(board[x][y])
        {
            if(record[x][y] < BRIGHTNESS_LEVELS) record[x][y] += 1;
        } 
        else record[x][y] = 0;
    }
}