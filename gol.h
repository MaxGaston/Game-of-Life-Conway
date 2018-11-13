#include <SDL.h>

// Colors
#define WHITE 255, 255, 255, 255
#define BLACK 0, 0, 0, 255
#define RED 255, 0, 0, 255
#define GREEN 0, 255, 0, 255
#define BLUE 0, 0, 255, 255

// Board constants
#define WIDTH 200
#define HEIGHT 100
#define START_ALIVE 10000
#define CELLS WIDTH * HEIGHT
#define for_x for (int x = 0; x < WIDTH; x++)
#define for_y for (int y = 0; y < HEIGHT; y++)
#define ATTEMPT_LIMIT 100000

// Cell constants
#define CWIDTH 4
#define CHEIGHT 4

//Screen constants
#define BORDER 20
#define SCREEN_WIDTH (WIDTH * CWIDTH) + BORDER
#define SCREEN_HEIGHT (HEIGHT * CHEIGHT) + BORDER

#define BRIGHTNESS_LEVELS 100

int init_gol(int board[WIDTH][HEIGHT], int num_alive);
void display(int board[WIDTH][HEIGHT], int record[WIDTH][HEIGHT], SDL_Renderer * rend);
int neighbors(int board[WIDTH][HEIGHT], int c, int r);
int nextState(int board[WIDTH][HEIGHT], int c, int r);
int nextGen(int board[WIDTH][HEIGHT]);
int addCells(int board[WIDTH][HEIGHT], int num);
int setCell(int board[WIDTH][HEIGHT], int record[WIDTH][HEIGHT], int x, int y, int state);
int reset(int board[WIDTH][HEIGHT], int num);
int killCells(int board[WIDTH][HEIGHT], int chance);
void updateRecord(int board[WIDTH][HEIGHT], int record[WIDTH][HEIGHT]);