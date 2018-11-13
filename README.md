# Game of Life-Conway

Conway's Game of Life, done in C with SDL.<br>

Cells transition from blue to red as they survive through consecutive generations.<br>

Compile: gcc main.c gol.c -o main.exe -std=c99 -lmingw32 -lSDL2main -lSDL2<br>

User controls:<br>
  * Left mouse click: add living cells at the cursor's position<br>
  * Right mouse click: kill cells at the cursor's position<br>
  * P: pause/resume the game<br>
  * R: reset the game with a new board of cells<br>
  * A: Add batches of living cells randomly to random positions<br>
  * K: Kill ~10% of the living cells<br>
  * SPACE: if the game is paused, step forward one generation<br>
  * ESCAPE: quit the program<br>
