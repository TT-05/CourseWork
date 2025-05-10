/*
 * DO NOT MODIFY THIS FILE.
 * ANY MODIFICATIONS TO THIS FILE WILL BE IGNORED EVEN IF
 * YOU SUBMIT THIS FILE, AS IT WILL BE REPLACED WITH THIS
 * ORIGINAL COPY. YOU ARE ONLY MEANT TO WRITE AND SUBMIT
 * THE IMPLEMENTATION FILE maze.c
 * YOU MAY ADD ANY ADDITIONAL HELPER FUNCTIONS AND TYPES YOU
 * NEED IN THAT IMPLEMENTATION FILE, BUT IT IS NOT NECESSARY
 * TO MODIFY THIS FILE
 */
#include "maze.h"
#include <stdio.h>
/*
 * This is the main that will use your main ADT.
 * It begins by calling your readMaze function to read
 * the maze in, and then continues by reading commands
 * from standard input from the user. The command
 * the user can give are as follows;
 *    p - to print the maze.
 *    q - to end the program.
 *    m - to make a move, the m must be followed by n, e, s, or w.
 *    r - to reset the maze by calling your reset function.
 * After reading all commands from the user your 
 * destroyMaze function is then called to clean up the maze.
*/

int whitespace(char c) {
  return c == ' ' || c == '\n' || c == '\n' || c == '\r';
}

char getNext() {
  char c = getchar();
  for (; whitespace(c); c = getchar());
  return c;
}

int main() {
  // This is the main for your maze program.
  // It does all the reading of input for you, and calls your appropriate
  // functions. All you have to do is implement the functions mentioned in
  // the assignment specification/declared in the provided maze.h file.
  struct Maze *m = readMaze();
  if (m == NULL) {
    printf("Malformed maze.\n");
    return 0;
  }
  printf("Finished reading maze, enter commands\n");
  char cmd;
  char target;
  int done = 0;
  int win = 0;
  while (!done && !feof(stdin)) {
    cmd = getNext();
    if (cmd == EOF) break; // breaks loop
    switch (cmd) {
      case 'p':
        printMaze(m);
        break; // breaks switch
      case 'q':
        done = 1;
        break; // breaks switch
      case 'm':
        target = getNext();
        if (target == EOF) {
          done = 1;
          break; // breaks switch
        }
        if (target != 'n' && target != 'e' && target != 's' && target != 'w') {
          printf("Invalid move target: %c\n", target);
        } else {
          struct Pos p = makeMove(m, target);
          if (p.x == -1 && p.y == -1) {
            done = 1;
            win = 1;
          }
        }
        break;
      case 'r':
        reset(m);
        break;
      default:
        printf("Incorrect command: %c\n", cmd);
        break;
    }
  }
  if (win) {
    printf("Congrats you made it to the end of the maze!\n");
    printMaze(m);
  }
  m = destroyMaze(m);
  if (m != NULL) {
    printf("Error, your destroyMaze doesn't return NULL\n");
  }
}
